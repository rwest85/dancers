#pragma once

static int parse_questions(dancers_parse *parse) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  size_t length = parse->header.length;
  dancers_packet *packet = &(parse->header.packet);
  TRACE_START();

  TRACE("parsing questions (%zu)", packet->qd_count);

  size_t count = packet->qd_count;
  size_t minimum_size = count * MIN_QUESTION_SZ;

  if (*offset + minimum_size >= length) return DE_PACKET_PARSE;

  for (size_t i = 0; i < count; i++) {
    char *name = parse_name_internal(parse);
    if (name == NULL || (*offset + QUESTION_POSTNAME_SZ) >= length) {
      questions_free(packet->questions, count);
      return DE_PACKET_PARSE;
    } else {
      dancers_q *question = &(packet->questions[i].q);
      question->name = name;

      question->type = read_uint16(data, offset);
      question->cls = read_uint16(data, offset);
    }
  }

  return DE_SUCCESS;
}

static int parse_rr_internal(dancers_parse *parse, dancers_rr *record) {
  int rc = DE_SUCCESS;

  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  size_t length = parse->header.length;
  TRACE_START();

  char *name = parse_name_internal(parse);
  if (name == NULL) {
    return DE_PACKET_PARSE;
  }

  if ((*offset + MIN_RR_SZ) > length) {
    DEBUG("Expected minimum of %zu bytes, found only %zu for rr", MIN_RR_SZ,
          (length - *offset));
    return DE_PACKET_PARSE;
  }

  record->name = name;
  record->type = read_uint16(data, offset);

  record->cls = read_uint16(data, offset);
  record->ttl = read_uint32(data, offset);

  size_t rdlen = read_uint16(data, offset);
  size_t expected_offset = *offset + rdlen;

  if (expected_offset > length) {
    DEBUG(
        "Expected end offset 0x%04zx is greater than packet length 0x%04zx, "
        "failing parse of rr type %04x",
        expected_offset, length, record->type);
    return DE_PACKET_PARSE;
  }

  dancers_rr_type type = record->type;

  /* find parse function */
  recordtype *rt = lookup_rt(type);

  if (rt && rt->parse_fn != NULL) {
    TRACE("Parsing RR with name '%s' and type %04x %s", name, type,
          type_to_string(type));
    if (rt->min_rdlen <= rdlen && rdlen <= rt->max_rdlen)
      rc = rt->parse_fn(parse, rdlen, record);
    else {
      DEBUG(
          "rdlen %zu is outside of bounds MIN %zu - %zu MAX for rr type %04x "
          "%s",
          rdlen, rt->min_rdlen, rt->max_rdlen, type, type_to_string(type));
      return DE_PACKET_PARSE;
    }
  } else {
    TRACE("Parsing generic RR with name '%s' type %04x %s rdlen %zu", name,
          type, type_to_string(type), rdlen);
    rc = parse_generic(parse, rdlen, record);
  }

  /* should consume entire *RDATA* portion */
  if (*offset < expected_offset) {
    DEBUG(
        "Packet parse warning: additional data (%zu bytes) while parsing rr "
        "type %04x expected end 0x%04zx actual end 0x%04zx",
        (expected_offset - *offset), record->type, expected_offset, length);

    *offset = expected_offset;
  } else if (*offset > expected_offset) {
    DEBUG(
        "Packet parse error: parsing rr type %04x expected end 0x%04zx actual "
        "end 0x%04zx",
        record->type, expected_offset, length);

    rc = DE_PACKET_PARSE;
  }

  TRACE("Completed parse rc=%d '%s' %04x %s", rc, name, type,
        type_to_string(type));
  return rc;
}

int parse_header(dancers_parse *parse) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  dancers_packet *packet = &(parse->header.packet);
  TRACE_START();

  packet->qid = read_uint16(data, offset);

  uint16_t flags = read_uint16(data, offset);

  packet->qr = !!(flags & 0x8000);
  packet->opcode = (flags & 0x7800) >> 11;
  packet->aa = !!(flags & (1 << 10));
  packet->tc = !!(flags & (1 << 9));
  packet->rd = !!(flags & (1 << 8));
  packet->ra = !!(flags & (1 << 7));
  packet->zz = !!(flags & (1 << 6));
  packet->ad = !!(flags & (1 << 5));
  packet->cd = !!(flags & (1 << 4));

  packet->rcode = (flags & 0x000F);

  packet->qd_count = read_uint16(data, offset);
  packet->an_count = read_uint16(data, offset);
  packet->ns_count = read_uint16(data, offset);
  packet->ar_count = read_uint16(data, offset);

  return DE_SUCCESS;
}

static dancers_error dancers_packet_parse_internal(dancers_parse *parse) {
  dancers_packet *packet = &(parse->header.packet);
  size_t length = parse->header.length;
  size_t *offset = &(parse->header.offset);

  /* parse header */
  TRACE_START();
  int rc = parse_header(parse);

  const size_t min_size =
      packet->qd_count * MIN_QUESTION_SZ +
      (packet->an_count + packet->ns_count + packet->ar_count) * MIN_RR_SZ;

  if (min_size > length) {
    DEBUG(
        "Packet with %zu questions and %zu/%zu/%zu rr has min length %zu > "
        "this "
        "packet length %zu",
        packet->qd_count, packet->an_count, +packet->ns_count, packet->ar_count,
        min_size, length);
    free(packet);
    return DE_PACKET_PARSE;
  }

  size_t rr_count = packet->an_count + packet->ns_count + packet->ar_count;

  packet->questions = parse->header.rest;
  packet->answers = &(packet->questions[packet->qd_count]);
  packet->nameservers = &(packet->answers[packet->an_count]);
  packet->additional = &(packet->nameservers[packet->ns_count]);
  parse->header.rest = &(packet->additional[packet->ar_count]);

  size_t allocated = parse->header.end - (void *)parse;
  size_t required = (void *)parse->header.rest - (void *)parse;
  if (required > allocated) {
    DEBUG(
        "Packet required %zu bytes to track all RRs, but only %zu were "
        "allocated",
        required, allocated);

    free(packet);
    return DE_PACKET_PARSE;
  }

  if (rc == DE_SUCCESS) {
    rc = parse_questions(parse);
  }

  if (rc == DE_SUCCESS) {
    for (size_t i = 0; i < rr_count; i++) {
      dancers_rr *base = &(packet->answers[i]);

      rc = parse_rr_internal(parse, base);

      if (rc != DE_SUCCESS) {
        break;
      }
    }
  }

  return rc;
}

dancers_error dancers_packet_parse(const uint8_t *data, size_t length,
                                   dancers_packet **_packet) {
  /* minimum packet size */
  if (length < MIN_HEADER_SZ) return DE_PACKET_PARSE;

  dancers_parse *parse = calloc(65536, 1);
  parse->header.data = data;
  parse->header.length = length;

  dancers_packet *packet = &(parse->header.packet);
  parse->header.end = (void *)parse + 65536;
  size_t o = (sizeof(dancers_parse_header) + sizeof(dancers_rr) - 1) /
             sizeof(dancers_rr);
  parse->header.rest = &(parse->records[o]);

  int rc = dancers_packet_parse_internal(parse);

  if (rc == DE_SUCCESS) *_packet = packet;

  return rc;
}

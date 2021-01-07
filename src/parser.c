#pragma once
#include "internal.h"
#include "parse_records.c"
#include "parse_scalar.c"
#include "records.c"

static int parse_questions(const uint8_t *data, size_t *offset, size_t length,
                           dancers_packet *packet) {
  size_t count = packet->qd_count;
  size_t minimum_size = count * MIN_QUESTION_SZ;

  if (*offset + minimum_size >= length) return DE_PACKET_PARSE;

  if (count > 0) {
    /* allocate space for questions */
    dancers_q *questions = calloc(sizeof(dancers_q), count);

    for (size_t i = 0; i < count; i++) {
      char *name = parse_name(data, offset, length);
      if (name == NULL || (*offset + QUESTION_POSTNAME_SZ) >= length) {
        questions_free(questions, count);
        return DE_PACKET_PARSE;
      } else {
        dancers_q *question = &questions[i];
        question->name = name;

        question->type = read_uint16(data, offset);
        question->cls = read_uint16(data, offset);
      }
    }
    packet->questions = questions;
  }

  return DE_SUCCESS;
}

static int parse_rr(const uint8_t *data, size_t *offset, size_t length,
                    dancers_rr *record) {
  TRACE_START();
  int rc = DE_SUCCESS;

  char *name = parse_name(data, offset, length);
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
      rc = rt->parse_fn(data, offset, length, rdlen, record);
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
    rc = parse_generic(data, offset, length, rdlen, record);
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

static int parse_rrset(const uint8_t *data, size_t *offset, size_t length,
                       size_t count, dancers_rr **_records) {
  int rc = DE_SUCCESS;

  if (count > 0) {
    /* allocate space */
    dancers_rr *records = calloc(sizeof(dancers_rr), count);
    if (records == NULL) {
      rc = DE_MALLOC_FAILED;
    } else {
      for (size_t i = 0; i < count; i++) {
        dancers_rr *base = &(records[i]);

        rc = parse_rr(data, offset, length, base);

        if (rc != DE_SUCCESS) {
          records_free(records, count);
          records = NULL;
          break;
        }
      }
    }
    *_records = records;
  }
  return rc;
}

int parse_header(const uint8_t *data, size_t *offset, dancers_packet *packet) {
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

dancers_error dancers_packet_parse(const uint8_t *data, size_t length,
                                   dancers_packet **packet) {
  /* minimum packet size */
  if (length < MIN_HEADER_SZ) return DE_PACKET_PARSE;

  *packet = calloc(65536, 1);

  size_t _offset = 0;
  size_t *offset = &_offset;
  TRACE_START();

  /* parse header */
  int rc = parse_header(data, offset, *packet);

  if (rc == DE_SUCCESS) {
    TRACE("parsing questions (%zu)", (*packet)->qd_count);
    rc = parse_questions(data, offset, length, *packet);
  }

  if (rc == DE_SUCCESS) {
    TRACE("parsing answers (%zu)", (*packet)->an_count);
    rc = parse_rrset(data, offset, length, (*packet)->an_count,
                     &((*packet)->answers));
  }

  if (rc == DE_SUCCESS) {
    TRACE("parsing nameserver records (%zu)", (*packet)->ns_count);
    rc = parse_rrset(data, offset, length, (*packet)->ns_count,
                     &((*packet)->nameservers));
  }

  if (rc == DE_SUCCESS) {
    TRACE("parsing additional records (%zu)", (*packet)->ar_count);
    rc = parse_rrset(data, offset, length, (*packet)->ar_count,
                     &((*packet)->additional));
  }

  if (rc != DE_SUCCESS) {
    dancers_packet_free(*packet);
    *packet = NULL;
  }

  return rc;
}

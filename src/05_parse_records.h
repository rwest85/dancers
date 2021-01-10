#pragma once
#include "000_internal.h"

const size_t MIN_HEADER_SZ = 12;
const size_t MIN_QUESTION_SZ = 5;
const size_t QUESTION_POSTNAME_SZ = 4;
const size_t MIN_RR_SZ = 9;

const size_t MIN_RDLEN = 0;
const size_t MAX_RDLEN = 0xFFFF - MIN_HEADER_SZ - MIN_RR_SZ;

/* records with fixed size */
const size_t A_RDLEN = IN_ADDR_SZ;
const size_t AAAA_RDLEN = IN6_ADDR_SZ;

/* if no attribute/value pairs, then rdlen can be zero */
/* if there is an attribute, minimum 4 bytes (option id, length) */
const size_t MIN_OPT_RDLEN = MIN_RDLEN;
const size_t MIN_OPT_ATTR = 4;

const size_t MIN_TXT_RDLEN = MIN_RDLEN;

/* records with just one name in rdata-- min rdlen is 1 */
const size_t MIN_NS_RDLEN = 1;
const size_t MIN_CNAME_RDLEN = 1;
const size_t MIN_PTR_RDLEN = 1;

const size_t MIN_MX_RDLEN = 3;
const size_t MIN_CAA_RDLEN = 2;
const size_t MIN_SRV_RDLEN = 7;
const size_t MIN_NAPTR_RDLEN = 8;
const size_t MIN_SOA_RDLEN = 22;

static int parse_txt(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  TRACE_START();

  dancers_rr_txt *txt = record;
  dancers_txt_contents *contents =
      calloc(2 * rdlen + sizeof(dancers_txt_contents), 1);

  const uint8_t *in = &data[*offset];
  char *out = contents->data;

  size_t end_offset = *offset + rdlen;

  /* offset to internal data */
  contents->part_offset = rdlen;
  char *indexes = contents->data + rdlen;

  /* record first offset 0 */
  *indexes++ = 0;

  /* TODO: combine with read_str */
  while (*offset < end_offset) {
    size_t l = *in++;
    *indexes++ = l;
    memcpy(out, in, l);

    out += l;
    in += l;
    (*offset) += (l + 1);
    contents->part_count++;
  }

  if (*offset == end_offset) {
    contents->length = out - contents->data;
    *(++out) = '\0';

    txt->contents = contents;
    return DE_SUCCESS;
  }

  free(contents);
  return DE_PACKET_PARSE;
}

static int parse_naptr(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  TRACE_START();
  dancers_rr_naptr *naptr = record;

  int rc = DE_PACKET_PARSE;

  TRACE("parsing NAPTR record with rdlen %zu", rdlen);

  naptr->order = read_uint16(parse);
  naptr->preference = read_uint16(parse);

  naptr->flags = read_str(parse);
  if (naptr->flags != NULL) naptr->service = read_str(parse);

  if (naptr->service != NULL)
    naptr->regexp = read_str(parse);

  if (naptr->regexp != NULL)
    naptr->replacement = parse_name_nocompression(parse);

  if (naptr->replacement != NULL) rc = DE_SUCCESS;

  TRACE("parsed NAPTR record rc=%d '%s' 0x%04x 0x%04x %s %s %s %s", rc,
        naptr->name, naptr->order, naptr->preference, naptr->flags,
        naptr->service, naptr->regexp, naptr->replacement);

  return rc;
}

static int parse_caa(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  TRACE_START();
  dancers_rr_caa *caa = record;
  int rc = DE_PACKET_PARSE;

  TRACE("parsing CAA record with rdlen %zu", rdlen);

  caa->flags = read_uint8(parse);

  size_t taglen = read_uint8(parse);
  size_t valuelen = rdlen - taglen - 2;

  caa->tag = calloc(taglen + 1, 1);
  caa->value = calloc(valuelen + 1, 1);

  if (caa->tag == NULL || caa->value == NULL) {
    rc = DE_MALLOC_FAILED;
  } else {
    memcpy(caa->tag, &data[*offset], taglen);
    (*offset) += taglen;

    memcpy(caa->value, &data[*offset], valuelen);
    (*offset) += valuelen;

    rc = DE_SUCCESS;
  }

  return rc;
}

static int parse_opt(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  TRACE_START();
  dancers_rr_opt *opt = record;
  int rc = DE_PACKET_PARSE;

  size_t end_offset = *offset + rdlen;

  /* count attribute records in RDATA */
  size_t count = 0;
  size_t cumulative_l = 0;
  size_t peek_offset = 2;
  while (*offset + peek_offset + 2 < end_offset) {
    uint16_t l = peek_uint16(data, peek_offset);
    peek_offset += l;
    cumulative_l += (l + 8) & ~7;
    count++;
  }
  TRACE("parsing OPT record with rdlen %zu attributes=%zu", rdlen, count);

  opt->attr_count = count;
  opt->attributes =
      calloc(sizeof(dancers_opt_attributes) * count + cumulative_l, 1);
  if (opt->attributes == NULL) return DE_MALLOC_FAILED;

  size_t i = 0;
  uint8_t *out = (void *)&(opt->attributes[count + 1]);

  while ((*offset < end_offset) && (i < count)) {
    if (*offset + MIN_OPT_ATTR > end_offset) {
      return DE_PACKET_PARSE;
    }

    /* read uint16 option */
    uint16_t option = read_uint16(parse);

    /* read uint16 length */
    uint16_t l = read_uint16(parse);

    /* alloc, read length bytes */
    if (*offset + l > end_offset) return DE_PACKET_PARSE;

    uint8_t *bytes = out;
    memcpy(bytes, &data[*offset], l);

    opt->attributes[i].option = option;
    opt->attributes[i].length = l;
    opt->attributes[i].data = bytes;

    out += (l + 8) & ~7;

    TRACE(
        "read attribute %02zu attr=0x%04x length=0x%04x value='%.*s' at "
        "0x%04zx\n",
        i, option, l, (int)l, bytes, *offset - MIN_OPT_ATTR);

    i++;
    *offset += l;
  }

  rc = DE_SUCCESS;
  return rc;
}

static int parse_soa(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  size_t length = parse->header.length;
  TRACE_START();
  dancers_rr_soa *soa = record;
  int rc = DE_PACKET_PARSE;

  soa->mname = parse_name(parse);
  if (soa->mname != NULL) soa->rname = parse_name(parse);

  if (soa->rname != NULL && *offset + 20 <= length) {
    soa->serial = read_uint32(parse);
    soa->refresh = read_uint32(parse);
    soa->retry = read_uint32(parse);
    soa->expire = read_uint32(parse);
    soa->minimum = read_uint32(parse);
    rc = DE_SUCCESS;
  }

  return rc;
}

static int parse_srv(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);

  dancers_rr_srv *srv = record;
  int rc = DE_PACKET_PARSE;

  srv->priority = read_uint16(parse);
  srv->weight = read_uint16(parse);
  srv->port = read_uint16(parse);

  /* rfc is ambiguous about compression, so support it */
  srv->target = parse_name(parse);
  if (srv->target != NULL) rc = DE_SUCCESS;

  return rc;
}

static int parse_mx(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  size_t length = parse->header.length;
  dancers_rr_mx *mx = record;
  int rc = DE_PACKET_PARSE;

  mx->preference = read_uint16(parse);

  mx->mx = parse_name(parse);
  if (mx->mx != NULL) rc = DE_SUCCESS;

  return rc;
}

static int parse_ptr(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  size_t length = parse->header.length;

  dancers_rr_ptr *ptr = record;
  int rc = DE_PACKET_PARSE;

  ptr->ptr = parse_name(parse);
  if (ptr->ptr != NULL) rc = DE_SUCCESS;

  return rc;
}

static int parse_cname(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  size_t length = parse->header.length;
  dancers_rr_cname *cname = record;
  int rc = DE_PACKET_PARSE;

  cname->cname = parse_name(parse);
  if (cname->cname != NULL) rc = DE_SUCCESS;

  return rc;
}

static int parse_ns(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  size_t length = parse->header.length;
  dancers_rr_ns *ns = record;
  int rc = DE_PACKET_PARSE;

  ns->nameserver = parse_name(parse);
  if (ns->nameserver != NULL) rc = DE_SUCCESS;

  return rc;
}

static int parse_a(dancers_parse *parse, size_t rdlen, void *record) {
  dancers_rr_a *a = record;

  a->addr = read_sockaddr_in(parse);

  return DE_SUCCESS;
}

static int parse_aaaa(dancers_parse *parse, size_t rdlen, void *record) {
  dancers_rr_aaaa *aaaa = record;

  aaaa->addr6 = read_sockaddr_in6(parse);

  return DE_SUCCESS;
}

static int parse_generic(dancers_parse *parse, size_t rdlen, void *record) {
  const uint8_t *data = parse->header.data;
  size_t *offset = &(parse->header.offset);
  dancers_rr_generic *generic = record;
  int rc = DE_PACKET_PARSE;

  uint8_t *rdata = calloc(rdlen + 1, 1);
  if (rdata == NULL) {
    rc = DE_MALLOC_FAILED;
  } else {
    memcpy(rdata, &data[*offset], rdlen);
    (*offset) = (*offset) + rdlen;

    generic->rdlen = rdlen;
    generic->rdata = rdata;
    rc = DE_SUCCESS;
  }
  return rc;
}

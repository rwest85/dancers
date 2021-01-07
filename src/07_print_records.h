#pragma once
#include <arpa/inet.h>

static int print_name(FILE *f, const char *name) {
  if (name == NULL || name[0] == '\0')
    return fprintf(f, ". ");
  else
    return fprintf(f, "%s ", name);
}

static int print_bytes(FILE *f, const uint8_t *data, size_t length) {
  int rc = 0;
  for (size_t i = 0; i < length; i++) rc += fprintf(f, " %02x", data[i]);
  return rc;
}

static int print_generic(FILE *f, const void *_record) {
  const dancers_rr_generic *record = _record;
  int rc = print_name(f, record->name);

  const char *type = type_to_string(record->type);

  if (type == NULL)
    rc += fprintf(f, "%3u", record->type);
  else
    rc += fprintf(f, "%s", type);

  print_bytes(f, record->rdata, record->rdlen);

  return rc;
}

static int print_opt(FILE *f, const void *record) {
  const dancers_rr_opt *opt = record;
  int rc = print_name(f, opt->name);
  rc += fprintf(f, "OPT UDPsize=%u 0x%08x", opt->max_udp_size,
                opt->extended_rcode);

  for (size_t i = 0; i < opt->attr_count; i++) {
    rc += fprintf(f, "0x%04x", opt->attributes[i].option);
    rc += print_bytes(f, opt->attributes[i].data, opt->attributes[i].length);
  }

  return rc;
}

static int dancers_print_qq(FILE *f, const void *_record) {
  const dancers_rr *record = _record;
  int rc = print_name(f, record->name);

  const char *type = type_to_string(record->type);

  if (type == NULL)
    rc += fprintf(f, "%3u?", record->type);
  else
    rc += fprintf(f, "%s?", type);

  return rc;
}

static int print_txt(FILE *f, const void *_record) {
  const dancers_rr_txt *txt = _record;

  int rc = print_name(f, txt->name);

  rc += fprintf(f, "TXT |%.*s|%s", (int)txt->contents->length,
                txt->contents->data,
                txt->contents->nonprintable ? " nonprintable" : "");

  if (txt->contents->part_count > 1) {
    char *offsets = txt->contents->data + txt->contents->part_offset;

    rc += fprintf(stderr, " parts %u offsets", txt->contents->part_count);

    for (size_t j = 0; j < txt->contents->part_count; j++) {
      rc += fprintf(f, " %02x", (uint8_t)offsets[j]);
    }
  }

  return rc;
}

static int print_caa(FILE *f, const void *_record) {
  const dancers_rr *record = _record;
  int rc = print_name(f, record->name);
  rc += fprintf(f, "CAA %3u %s \"%s\"", record->caa.flags, record->caa.tag,
                record->caa.value);
  return rc;
}

static int print_ns(FILE *f, const void *_record) {
  const dancers_rr *record = _record;
  int rc = print_name(f, record->name);
  rc += fprintf(f, "NS %s", record->ns.ns);
  return rc;
}

static int print_a(FILE *f, const void *_record) {
  const dancers_rr *record = _record;
  char buf[64] = {0};

  int rc = print_name(f, record->name);
  inet_ntop(AF_INET, &(record->a.addr.sin_addr), buf, sizeof(buf));

  rc += fprintf(f, "A %s", buf);
  return rc;
}

static int print_cname(FILE *f, const void *_record) {
  const dancers_rr *record = _record;
  int rc = print_name(f, record->name);
  rc += fprintf(f, "CNAME %s", record->cname.cname);
  return rc;
}

static int print_soa(FILE *f, const void *_record) {
  const dancers_rr_soa *soa = _record;
  int rc = print_name(f, soa->name);
  rc += fprintf(f, "SOA ");
  rc += print_name(f, soa->mname);
  rc += print_name(f, soa->rname);
  rc += fprintf(f, "%u %u %u %u %u", soa->serial, soa->refresh, soa->retry,
                soa->expire, soa->minimum);
  return rc;
}

static int print_ptr(FILE *f, const void *_record) {
  const dancers_rr *record = _record;
  int rc = print_name(f, record->name);
  rc += fprintf(f, "PTR %s", record->ptr.ptr);
  return rc;
}

static int print_mx(FILE *f, const void *_record) {
  const dancers_rr *record = _record;
  int rc = print_name(f, record->name);
  rc += fprintf(f, "MX %s", record->mx.mx);
  return rc;
}

static int print_aaaa(FILE *f, const void *_record) {
  const dancers_rr_aaaa *aaaa = _record;
  char buf[64] = {0};

  int rc = print_name(f, aaaa->name);
  inet_ntop(AF_INET6, &(aaaa->addr6.sin6_addr), buf, sizeof(buf));

  rc += fprintf(f, "AAAA %s", buf);
  return rc;
}

static int print_srv(FILE *f, const void *_record) {
  const dancers_rr_srv *srv = _record;
  int rc = print_name(f, srv->name);
  rc += fprintf(f, "SRV %u %u %u %s", srv->priority, srv->weight, srv->port,
                srv->target);
  return rc;
}

static int print_naptr(FILE *f, const void *_record) {
  const dancers_rr_naptr *naptr = _record;
  int rc = print_name(f, naptr->name);
  rc += fprintf(f, "NAPTR %u %u %s %s %s", naptr->order, naptr->preference,
                naptr->flags, naptr->service, naptr->regexp);
  rc += print_name(f, naptr->replacement);
  return rc;
}

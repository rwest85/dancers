#pragma once

#include "internal.h"
#include "print_records.c"

static int dancers_print_rr(FILE *f, const void *_record) {
  const dancers_rr *record = _record;

  recordtype *rt = lookup_rt(record->type);
  print_fn print_fn = (rt && rt->print_fn) ? rt->print_fn : print_generic;

  return print_fn(f, record);
}

static int print_rrset(FILE *f, const dancers_rr *rrset, size_t count) {
  int rc = 0;
  for (size_t i = 0; i < count; i++) {
    rc += dancers_print_rr(f, &rrset[i]);
    rc += fprintf(f, i < (count - 1) ? ", " : "");
  }
  return rc;
}

int dancers_packet_print(FILE *f, const dancers_packet *packet) {
  if (f == NULL || packet == NULL) return -1;

  int rc = 0;
  size_t i = 0;

  rc += fprintf(f, "qid 0x%04x %c", packet->qid, packet->qr ? 'R' : 'Q');

  if (packet->opcode != OP_QUERY)
    rc += fprintf(f, "(%s %01x) ", opcode_to_string(packet->opcode),
                  packet->opcode);

  rc += fprintf(f, "(%s %s %s %s %s %s%s %01d%01d%01d%01d%01d%01d%01d) ",
                packet->aa ? "AA" : "aa", packet->tc ? "TC" : "tc",
                packet->rd ? "RD" : "rd", packet->ra ? "RA" : "ra",
                packet->ad ? "AD" : "ad", packet->cd ? "CD" : "cd",
                packet->zz ? " ZZ" : "", packet->cd, packet->ad, packet->zz,
                packet->ra, packet->rd, packet->tc, packet->aa);

  for (i = 0; i < packet->qd_count; i++) {
    rc += dancers_print_qq(f, &(packet->questions[i]));
    rc += fprintf(f, i < packet->qd_count - 1 ? ", " : "");
  }

  if (packet->rcode != RC_NOERROR)
    rc += fprintf(f, " %s", rcode_to_string(packet->rcode));
  rc += fprintf(f, " %zu/%zu/%zu ", packet->an_count, packet->ns_count,
                packet->ar_count);

  rc += print_rrset(f, packet->answers, packet->an_count);
  rc += fprintf(f, " / ");

  rc += print_rrset(f, packet->nameservers, packet->ns_count);
  rc += fprintf(f, " / ");

  rc += print_rrset(f, packet->additional, packet->ar_count);
  fprintf(f, "\n");

  return rc;
}

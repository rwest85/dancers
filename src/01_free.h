#pragma once
#include "000_internal.h"

static void record_clear(void *_record) {
  dancers_rr *record = _record;
  free(record->name);

  recordtype *rt = lookup_rt(record->type);
  if (rt && rt->free_fn) {
    rt->free_fn(record);
  } else {
    free_generic(record);
  }
}

static void records_free(dancers_rr *records, size_t count) {
  if (count > 0 && records != NULL) {
    for (size_t i = 0; i < count; i++) record_clear(&records[i]);
  }
  free(records);
}

void dancers_packet_free(dancers_packet *packet) {
  if (packet) {
    questions_free(packet->questions, packet->qd_count);
    records_free(packet->answers, packet->an_count);
    records_free(packet->nameservers, packet->ns_count);
    records_free(packet->additional, packet->ar_count);

    free(packet);
  }
}

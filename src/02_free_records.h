#pragma once
#include "000_internal.h"

typedef struct dancers_rr_free {
  DANCERS_RR_BASE_ELEMENTS;
  void *p1;
  void *p2;
  void *p3;
  void *p4;
} dancers_rr_free;

static void questions_free(dancers_q *questions, size_t count) {
  if (count > 0 && questions != NULL) {
    for (size_t i = 0; i < count; i++)
      if (questions[i].name) free(questions[i].name);
  }
  free(questions);
}

static void clear_noop(void *_unused) {}

static void clear_rec_1(dancers_rr_free *record) { free(record->p1); }

static void clear_rec_2(dancers_rr_free *record) {
  free(record->p1);
  free(record->p2);
}

static void clear_rec_4(dancers_rr_free *record) {
  free(record->p1);
  free(record->p2);
  free(record->p3);
  free(record->p4);
}

const free_fn free_a = (free_fn)clear_noop;
const free_fn free_aaaa = (free_fn)clear_noop;

const free_fn free_mx = (free_fn)clear_rec_1;
const free_fn free_ns = (free_fn)clear_rec_1;
const free_fn free_opt = (free_fn)clear_rec_1;
const free_fn free_ptr = (free_fn)clear_rec_1;
const free_fn free_srv = (free_fn)clear_rec_1;
const free_fn free_txt = (free_fn)clear_rec_1;
const free_fn free_cname = (free_fn)clear_rec_1;
const free_fn free_generic = (free_fn)clear_rec_1;

const free_fn free_soa = (free_fn)clear_rec_2;
const free_fn free_caa = (free_fn)clear_rec_2;

const free_fn free_naptr = (free_fn)clear_rec_4;

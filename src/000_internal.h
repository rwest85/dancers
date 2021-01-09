#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/dancers.h"

typedef enum dancers_rr_type {
  t_a = 1,
  t_ns = 2,
  t_cname = 5,
  t_soa = 6,
  t_ptr = 12,
  t_mx = 15,
  t_txt = 16,
  t_aaaa = 28,
  t_srv = 33,
  t_naptr = 35,
  t_opt = 41,
  t_any = 255,
  t_caa = 257,
} dancers_rr_type;

#define MAX_DOMAINNAME_SZ 256

const uint16_t OP_QUERY = 0;

const uint16_t RC_NOERROR = 0;
const uint16_t RC_FORMERR = 1;
const uint16_t RC_SERVFAIL = 2;
const uint16_t RC_NXDOMAIN = 3;
const uint16_t RC_NOTIMPL = 4;
const uint16_t RC_REFUSED = 5;
const uint16_t RC_YXDOMAIN = 6;
const uint16_t RC_YXRRSET = 7;
const uint16_t RC_NXRRSET = 8;
const uint16_t RC_NOTAUTH = 9;
const uint16_t RC_NOTZONE = 10;
const uint16_t RC_BADSIG = 16;
const uint16_t RC_BADKEY = 17;
const uint16_t RC_BADTIME = 18;

const char *opcode_to_string(uint16_t opcode);
const char *rcode_to_string(uint16_t rcode);
const char *cls_to_string(uint16_t cls);
const char *type_to_string(uint16_t type);

static int dancers_print_rr(FILE *f, const void *_record);

typedef int (*parse_fn)(const uint8_t *data, size_t *offset, size_t length,
                        size_t rdlen, void *record);
typedef int (*print_fn)(FILE *f, const void *record);
typedef void *(*free_fn)(void *record);

typedef struct recordtype {
  dancers_rr_type type;
  size_t min_rdlen;
  size_t max_rdlen;
  parse_fn parse_fn;
  free_fn free_fn;
  print_fn print_fn;
} recordtype;

static void questions_free(dancers_rr *questions, size_t count);
static void record_clear(void *_record);
static void records_free(dancers_rr *records, size_t count);

recordtype *lookup_rt(dancers_rr_type type);

typedef struct dancers_parse_header {
  struct dancers_packet packet;
  dancers_rr *rest;
  void *end;
} dancers_parse_header;

typedef struct dancers_parse {
  union {
    dancers_parse_header header;
    dancers_rr records[16];
  };
} dancers_parse;

/** tracing and debug */
#ifndef TRACE_ON
#define TRACE_START(...)
#define TRACE(...)
#define TRACE_SOCKET(...)
#endif

#ifndef DEBUG_ON
#define DEBUG(...)
#endif

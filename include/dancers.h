#pragma once
#ifndef DANCERS_H
#define DANCERS_H

/* TODO: make stdio optional */
#include <netinet/in.h>
#include <stdio.h> /* FILE * for print fn */

typedef enum dancers_error dancers_error;
typedef struct dancers_packet dancers_packet;

dancers_error dancers_packet_parse(const uint8_t *data, size_t length,
                                   dancers_packet **packet);
void dancers_packet_free(dancers_packet *packet);
int dancers_packet_print(FILE *f, const dancers_packet *packet);

/* declarations of data structures */
typedef union dancers_rr dancers_rr;
typedef struct dancers_rr_base dancers_rr_base;
typedef dancers_rr_base dancers_q;

typedef struct dancers_packet {
  uint16_t qid;
  unsigned int qr : 1;
  unsigned int opcode : 4;
  unsigned int aa : 1;
  unsigned int tc : 1;
  unsigned int rd : 1;
  unsigned int ra : 1;
  unsigned int zz : 1;
  unsigned int ad : 1;
  unsigned int cd : 1;
  unsigned int rcode : 4;

  dancers_rr *questions;
  dancers_rr *answers;
  dancers_rr *nameservers;
  dancers_rr *additional;

  size_t qd_count;
  size_t an_count;
  size_t ns_count;
  size_t ar_count;

  dancers_rr *rest;
  void *end;
} dancers_packet;

typedef enum dancers_error {
  DE_SUCCESS = 0,
  DE_PACKET_PARSE = -1,
  DE_MALLOC_FAILED = -2,
} dancers_error;

#define DANCERS_RR_BASE_ELEMENTS \
  struct {                       \
    char *name;                  \
    uint16_t type;               \
    uint16_t cls;                \
    uint32_t ttl;                \
  }

typedef struct dancers_rr_base {
  DANCERS_RR_BASE_ELEMENTS;
} dancers_rr_base;

typedef struct dancers_rr_generic {
  DANCERS_RR_BASE_ELEMENTS;
  uint8_t *rdata;
  uint16_t rdlen;
} dancers_rr_generic;

typedef struct dancers_rr_a {
  DANCERS_RR_BASE_ELEMENTS;
  struct sockaddr_in addr;
} dancers_rr_a;

typedef struct dancers_rr_ns {
  DANCERS_RR_BASE_ELEMENTS;
  union {
    char *nameserver;
    char *ns;
  };
} dancers_rr_ns;

typedef struct dancers_rr_cname {
  DANCERS_RR_BASE_ELEMENTS;
  char *cname;
} dancers_rr_cname;

typedef struct dancers_rr_soa {
  DANCERS_RR_BASE_ELEMENTS;
  char *mname;
  char *rname;
  uint16_t serial;
  uint16_t refresh;
  uint16_t retry;
  uint16_t expire;
  uint16_t minimum;
} dancers_rr_soa;

typedef struct dancers_rr_ptr {
  DANCERS_RR_BASE_ELEMENTS;
  char *ptr;
} dancers_rr_ptr;

typedef struct dancers_rr_mx {
  DANCERS_RR_BASE_ELEMENTS;
  union {
    char *mx;
    char *exchange;
  };
  uint16_t preference;
} dancers_rr_mx;

typedef struct dancers_txt_contents {
  unsigned int length : 16;
  unsigned int part_offset : 16;
  unsigned int part_count : 16;
  unsigned int nonprintable : 1;
  char data[8];
} dancers_txt_contents;

typedef struct dancers_rr_txt {
  DANCERS_RR_BASE_ELEMENTS;
  dancers_txt_contents *contents;
} dancers_rr_txt;

typedef struct dancers_opt_attributes {
  uint16_t option;
  uint16_t length;
  uint8_t *data;
} dancers_opt_attributes;

typedef struct dancers_rr_opt {
  char *name;
  uint16_t type;
  uint16_t max_udp_size;   /* class */
  uint32_t extended_rcode; /* TTL   */

  dancers_opt_attributes *attributes;
  uint16_t attr_count;
} dancers_rr_opt;

typedef struct dancers_rr_aaaa {
  DANCERS_RR_BASE_ELEMENTS;
  struct sockaddr_in6 addr6;
} dancers_rr_aaaa;

typedef struct dancers_rr_srv {
  DANCERS_RR_BASE_ELEMENTS;
  char *target;
  uint16_t priority;
  uint16_t weight;
  uint16_t port;
} dancers_rr_srv;

typedef struct dancers_rr_naptr {
  DANCERS_RR_BASE_ELEMENTS;
  char *flags;
  char *service;
  char *regexp;
  char *replacement;
  uint16_t order;
  uint16_t preference;
} dancers_rr_naptr;

typedef struct dancers_rr_caa {
  DANCERS_RR_BASE_ELEMENTS;
  char *tag;
  char *value;
  uint8_t flags;
} dancers_rr_caa;

typedef union dancers_rr {
  DANCERS_RR_BASE_ELEMENTS;
  dancers_rr_base base;
  dancers_q q;
  dancers_rr_a a;
  dancers_rr_ns ns;
  dancers_rr_cname cname;
  dancers_rr_soa soa;
  dancers_rr_ptr ptr;
  dancers_rr_opt opt;
  dancers_rr_mx mx;
  dancers_rr_txt txt;
  dancers_rr_aaaa aaaa;
  dancers_rr_srv srv;
  dancers_rr_naptr naptr;
  dancers_rr_caa caa;
  dancers_rr_generic generic;
} dancers_rr;

#endif

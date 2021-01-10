#pragma once
#include "000_internal.h"

const size_t SOCKADDR_IN_SZ = sizeof(struct sockaddr_in);
const size_t IN_ADDR_SZ = sizeof(struct in_addr);

const size_t SOCKADDR_IN6_SZ = sizeof(struct sockaddr_in6);
const size_t IN6_ADDR_SZ = sizeof(struct in6_addr);

static inline uint8_t read_uint8(struct dancers_parse *parse) {
  /* ASSUMES: bytes between *offset and *offset+1 are in-bounds */

  uint8_t rtn = parse->header.data[parse->header.offset];
  parse->header.offset += sizeof(uint8_t);

  return rtn;
}

static inline uint16_t read_uint16(struct dancers_parse *parse) {

  /* ASSUMES: bytes between *offset and *offset+2 are in-bounds */
  uint16_t rtn = (parse->header.data[parse->header.offset] << 8) +
    parse->header.data[parse->header.offset + 1];

  parse->header.offset += sizeof(uint16_t);

  return rtn;
}

static inline uint16_t peek_uint16(const uint8_t *data, size_t peek_offset) {
  return (data[peek_offset] << 8) + data[peek_offset + 1];
}

static inline uint32_t read_uint32(struct dancers_parse *parse) {
  /* ASSUMES: bytes between *offset and *offset+4 are in-bounds */
  uint16_t hi = read_uint16(parse);
  uint16_t lo = read_uint16(parse);

  return (hi << 16) | lo;
}

static inline struct sockaddr_in read_sockaddr_in(struct dancers_parse *parse) {
  struct sockaddr_in addr = {
      .sin_len = SOCKADDR_IN_SZ,
      .sin_family = AF_INET,
  };

  memcpy(&addr.sin_addr, &parse->header.data[parse->header.offset], IN_ADDR_SZ);
  parse->header.offset += IN_ADDR_SZ;

  return addr;
}

static inline struct sockaddr_in6 read_sockaddr_in6(struct dancers_parse *parse) {
  struct sockaddr_in6 addr6 = {
      .sin6_len = SOCKADDR_IN6_SZ,
      .sin6_family = AF_INET6,
  };

  memcpy(&addr6.sin6_addr,  &parse->header.data[parse->header.offset], IN6_ADDR_SZ);
  parse->header.offset += IN6_ADDR_SZ;

  return addr6;
}

#pragma once
#include "internal.h"

const size_t SOCKADDR_IN_SZ = sizeof(struct sockaddr_in);
const size_t IN_ADDR_SZ = sizeof(struct in_addr);

const size_t SOCKADDR_IN6_SZ = sizeof(struct sockaddr_in6);
const size_t IN6_ADDR_SZ = sizeof(struct in6_addr);

static inline uint8_t read_uint8(const uint8_t *data, size_t *offset) {
  /* ASSUMES: bytes between *offset and *offset+1 are in-bounds */
  uint16_t rtn = data[*offset];
  *offset = *offset + sizeof(uint8_t);
  return rtn;
}

static inline uint16_t read_uint16(const uint8_t *data, size_t *offset) {
  /* ASSUMES: bytes between *offset and *offset+2 are in-bounds */
  uint16_t rtn = (data[*offset] << 8) + data[*offset + 1];
  *offset = *offset + sizeof(uint16_t);
  return rtn;
}

static inline uint16_t peek_uint16(const uint8_t *data, size_t peek_offset) {
  return (data[peek_offset] << 8) + data[peek_offset + 1];
}

static inline uint32_t read_uint32(const uint8_t *data, size_t *offset) {
  /* ASSUMES: bytes between *offset and *offset+4 are in-bounds */
  uint16_t hi = read_uint16(data, offset);
  uint16_t lo = read_uint16(data, offset);

  return (hi << 16) | lo;
}

static inline struct sockaddr_in read_sockaddr_in(const uint8_t *data,
                                                  size_t *offset) {
  struct sockaddr_in addr = {
      .sin_len = SOCKADDR_IN_SZ,
      .sin_family = AF_INET,
  };

  memcpy(&addr.sin_addr, &data[*offset], IN_ADDR_SZ);
  (*offset) += IN_ADDR_SZ;

  return addr;
}

static inline struct sockaddr_in6 read_sockaddr_in6(const uint8_t *data,
                                                    size_t *offset) {
  struct sockaddr_in6 addr6 = {
      .sin6_len = SOCKADDR_IN6_SZ,
      .sin6_family = AF_INET6,
  };

  memcpy(&addr6.sin6_addr, &data[*offset], IN6_ADDR_SZ);
  (*offset) += IN6_ADDR_SZ;

  return addr6;
}
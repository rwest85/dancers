#pragma once

#ifdef TRACE_ON
#include <arpa/inet.h>

#define TRACE_START(...)					    \
  size_t __trace_start_offset = parse->header.offset;		    \
  fprintf(stderr, "T entering %s start_offset=0x%04zx\n", __func__, \
          __trace_start_offset);

#define TRACE(format, ...)                                            \
  fprintf(stderr, "T %s " format " start_offset=0x%04zx\n", __func__, \
          __VA_ARGS__, __trace_start_offset)

#define TRACE_SOCKET(socket, format, ...)                                     \
  {                                                                           \
    struct sockaddr_in *_s = (void *)socket;                                  \
    char _trace_buf[64] = {0};                                                \
    inet_ntop(_s->sin_family, &_s->sin_addr, _trace_buf, sizeof(_trace_buf)); \
    TRACE(format, _trace_buf, __VA_ARGS__);                                   \
  }

#endif /* TRACE_ON */

#ifdef DEBUG_ON

#define DEBUG(format, ...)                                                   \
  fprintf(stderr, "D %s %s:%04u " format "\n", __func__, __FILE__, __LINE__, \
          __VA_ARGS__);

#endif /* DEBUG_ON */

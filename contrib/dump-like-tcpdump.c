#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "funcattrs.h"
#include "netdissect.h"
#include "print.h"

// install and build libpcap, tcpdump
// compile with -I -L to tcpdump directory, eg:
//
// export TCPDUMP_DIR=../tcpdump
// clang -I${TCPDUMP_DIR} -L${TCPDUMP_DIR} -Wall -g -O0
// contrib/dump-like-tcpdump.c -lnetdissect -lpcap -o dump-like-tcpdump

// forward declarations
static int dump_vfprintf(netdissect_options *ndo, const char *fmt, ...);
const uint8_t fixture_dns_response[];
const size_t fixture_dns_response_len;

// dump_domain_packet: dump domain packet to stderr
void dump_domain_packet(const uint8_t *data, size_t length) {
  netdissect_options ndo = {
      .ndo_printf = dump_vfprintf,  // printf: output function
      .ndo_vflag = 3,               // vflag: verbosity (see below)
      .ndo_snaplen = 1500,          // snaplen: length of snapshot (packet)
      .ndo_snapend =
          (data + length),  // snapend must point to end of *this packet*
  };

  const int is_tcp = 0;   // true when packet preceded by 2-byte length
  const int is_mdns = 0;  // true when data represents multicast DNS
  domain_print(&ndo, data, length, is_tcp, is_mdns);

  // no newline after domain_print
  fprintf(stderr, "\n");
}

// sample driver function
int main() {
  // offset from start of ethernet frame to DNS UDP data
  const size_t offset = 42;

  // the fixture (above) is a whole ethernet frame
  const uint8_t *frame = fixture_dns_response;

  const uint8_t *data = frame + offset;
  size_t length = fixture_dns_response_len - offset;

  dump_domain_packet(data, length);

  return 0;
}

// Notes: vflag controls verbosity
// vflag 0 - print type, value for each rr
//
// 49834*- 4/0/1 NS ns-1527.awsdns-62.org., NS ns-1926.awsdns-48.co.uk., NS
// ns-282.awsdns-35.com., NS ns-670.awsdns-19.net. (193)
//
// vflag 1 - also print query, and name of each rr
//
// 49834*- 4/0/1 delegation-test.ventx.de. NS ns-1527.awsdns-62.org.,
// delegation-test.ventx.de. NS ns-1926.awsdns-48.co.uk.,
// delegation-test.ventx.de. NS ns-282.awsdns-35.com., delegation-test.ventx.de.
// NS ns-670.awsdns-19.net. (193)
//
// vflag 3 - also print TTL of each rr (in humanized units eg [2d] = 2 days =
// 172800 sec)
//
// 49834*- q: NS? delegation-test.ventx.de. 4/0/1 delegation-test.ventx.de. [2d]
// NS ns-1527.awsdns-62.org., delegation-test.ventx.de. [2d] NS
// ns-1926.awsdns-48.co.uk., delegation-test.ventx.de. [2d] NS
// ns-282.awsdns-35.com., delegation-test.ventx.de. [2d] NS
// ns-670.awsdns-19.net. ar: . OPT UDPsize=4096 (193)
//
// Details: 49834*- q: NS? delegation-test.ventx.de. 4/0/1
// delegation-test.ventx.de. [2d] NS ns-1527.awsdns-62.org. ... ar: . OPT
// UDPsize=4096 (193)
//          1    23 4   5  6                         7     8 9    A  B C   D E
//          F            G
//
// Legend:
// 1: packet qid
// 2: authoritative answer flag set
// 3: recursion requested but not available

const uint8_t fixture_dns_response[] = {
    0x80,       0xe6, 0x50, 0x24, 0xc1,       0xf6, 0xa8, 0x4e, 0x3f, 0xdf,
    0x41,       0x12, 0x08, 0x00, 0x45,       0x00, 0x00, 0xdd, 0x01, 0x06,
    0x00,       0x00, 0xf6, 0x11, 0x72,       0x1f, 0xcd, 0xfb, 0xc1, 0x1a,
    0xc0,       0xa8, 0x01, 0x2c, 0x00,       0x35, 0xc1, 0xab, 0x00, 0xc9,
    0xbd,       0xa0, 0xc2, 0xaa, 0x85,       0x00, 0x00, 0x01, 0x00, 0x04,
    0x00,       0x00, 0x00, 0x01, /*1*/ 0x0f, 0x64, 0x65, 0x6c, 0x65, 0x67,
    0x61,       0x74, 0x69, 0x6f, 0x6e,       0x2d, 0x74, 0x65, 0x73, 0x74,
    0x05,       0x76, 0x65, 0x6e, 0x74,       0x78, 0x02, 0x64, 0x65, 0x00,
    0x00,       0x02, 0x00, 0x01, 0xc0,       0x0c, 0x00, 0x02, 0x00, 0x01,
    0x00,       0x02, 0xa3, 0x00, 0x00,       0x17,
    /*2*/ 0x07, 0x6e, 0x73, 0x2d, 0x31,       0x35, 0x32, 0x37, 0x09, 0x61,
    0x77,       0x73, 0x64, 0x6e, 0x73,       0x2d, 0x36, 0x32, 0x03, 0x6f,
    0x72,       0x67, 0x00, 0xc0, 0x0c,       0x00, 0x02, 0x00, 0x01, 0x00,
    0x02,       0xa3, 0x00, 0x00, 0x19,       0x07, 0x6e, 0x73, 0x2d, 0x31,
    0x39,       0x32, 0x36, 0x09, 0x61,       0x77, 0x73, 0x64, 0x6e, 0x73,
    0x2d,       0x34, 0x38, 0x02, 0x63,       0x6f, 0x02, 0x75, 0x6b, 0x00,
    0xc0,       0x0c, 0x00, 0x02, 0x00,       0x01, 0x00, 0x02, 0xa3, 0x00,
    0x00,       0x16, 0x06, 0x6e, 0x73,       0x2d, 0x32, 0x38, 0x32, 0x09,
    0x61,       0x77, 0x73, 0x64, 0x6e,       0x73, 0x2d, 0x33, 0x35, 0x03,
    0x63,       0x6f, 0x6d, 0x00, 0xc0,       0x0c, 0x00, 0x02, 0x00, 0x01,
    0x00,       0x02, 0xa3, 0x00, 0x00,       0x16, 0x06, 0x6e, 0x73, 0x2d,
    0x36,       0x37, 0x30, 0x09, 0x61,       0x77, 0x73, 0x64, 0x6e, 0x73,
    0x2d,       0x31, 0x39, 0x03, 0x6e,       0x65, 0x74, 0x00, 0x00, 0x00,
    0x29,       0x10, 0x00, 0x00, 0x00,       0x00, 0x00, 0x00, 0x00};
const size_t fixture_dns_response_len = sizeof(fixture_dns_response);

// vfprintf-style function called from `netdissect`
static int dump_vfprintf(netdissect_options *ndo, const char *fmt, ...) {
  va_list ap;
  va_start(ap, fmt);

  int rc = vfprintf(stderr, fmt, ap);

  va_end(ap);
  return rc;
}

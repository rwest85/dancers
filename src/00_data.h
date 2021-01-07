#pragma once

#include "000_internal.h"

const uint8_t QR_QUERY = 0;
const uint8_t QR_RESPONSE = 1;

const char *opcode_to_string(uint16_t opcode) {
  return opcode == 0 ? "OP_QUERY" : "?";
}

const uint16_t CLS_IN = 1;
const uint16_t CLS_ANY = 255;

const char *cls_to_string(uint16_t cls) { return cls == 0 ? "IN" : "  "; }

static const char *_rcodes[] = {
    "NOERROR", /* 0 */
    "FORMERR", "SERVFAIL", "NXDOMAIN", "NOTIMPL", "REFUSED", "YXDOMAIN",
    "YXRRSET", "NXRRSET",  "NOTAUTH",  "NOTZONE",                      /* 10 */
    "",        "",         "",         "",        "",        "BADSIG", /* 16 */
    "BADKEY",                                                          /* 17 */
    "BADTIME",                                                         /* 18 */
};

size_t _rcode_min = 0;
size_t _rcode_max = sizeof(_rcodes) / sizeof(_rcodes[0]);

const char *rcode_to_string(uint16_t rcode) {
  if (rcode >= _rcode_min && rcode < _rcode_max) return _rcodes[rcode];

  return "?";
}

static const char _types_0[][11] = {
    "",            // 0 (reserved)
    "A",           // 1
    "NS",          // 2
    "MD",          // 3
    "MF",          // 4
    "CNAME",       // 5
    "SOA",         // 6
    "MB",          // 7
    "MG",          // 8
    "MR",          // 9
    "NULL",        // 10
    "WKS",         // 11
    "PTR",         // 12
    "HINFO",       // 13
    "MINFO",       // 14
    "MX",          // 15
    "TXT",         // 16
    "RP",          // 17
    "AFSDB",       // 18
    "X25",         // 19
    "ISDN",        // 20
    "RT",          // 21
    "NSAP",        // 22
    "NSAP-PTR",    // 23
    "SIG",         // 24
    "KEY",         // 25
    "PX",          // 26
    "GPOS",        // 27
    "AAAA",        // 28
    "LOC",         // 29
    "NXT",         // 30
    "EID",         // 31
    "NIMLOC",      // 32
    "SRV",         // 33
    "ATMA",        // 34
    "NAPTR",       // 35
    "KX",          // 36
    "CERT",        // 37
    "A6",          // 38
    "DNAME",       // 39
    "SINK",        // 40
    "OPT",         // 41
    "APL",         // 42
    "DS",          // 43
    "SSHFP",       // 44
    "IPSECKEY",    // 45
    "RRSIG",       // 46
    "NSEC",        // 47
    "DNSKEY",      // 48
    "DHCID",       // 49
    "NSEC3",       // 50
    "NSEC3PARAM",  // 51
    "TLSA",        // 52
    "SMIMEA",      // 53
    "",            // 54 (unassigned)
    "HIP",         // 55
    "NINFO",       // 56
    "RKEY",        // 57
    "TALINK",      // 58
    "CDS",         // 59
    "CDNSKEY",     // 60
    "OPENPGPKEY",  // 61
    "CSYNC",       // 62
    "ZONEMD",      // 63
    "SVCB",        // 64
    "HTTPS",       // 65
};
static const size_t _type_min_0 = 0;
static const size_t _type_max_0 = 66;

static const char _types_1[][11] = {
    "SPF",     // 99
    "UINFO",   // 100
    "UID",     // 101
    "GID",     // 102
    "UNSPEC",  // 103
    "NID",     // 104
    "L32",     // 105
    "L64",     // 106
    "LP",      // 107
    "EUI48",   // 108
    "EUI64",   // 109
};
static const size_t _type_min_1 = 99;
static const size_t _type_max_1 = 110;

static const char _types_2[][11] = {
    "TKEY",      // 249
    "TSIG",      // 250
    "IXFR",      // 251
    "AXFR",      // 252
    "MAILB",     // 253
    "MAILA",     // 254
    "*",         // 255
    "URI",       // 256
    "CAA",       // 257
    "AVC",       // 258
    "DOA",       // 259
    "AMTRELAY",  // 260
};
static const size_t _type_min_2 = 249;
static const size_t _type_max_2 = 261;

const char *type_to_string(uint16_t type) {
  if (type >= _type_min_0 && type < _type_max_0)
    return _types_0[type];
  else if (type >= _type_min_1 && type < _type_max_1)
    return _types_1[type - _type_min_1];
  else if (type >= _type_min_2 && type < _type_max_2)
    return _types_2[type - _type_min_2];

  return NULL;
}

#pragma once
#include "free_records.c"
#include "internal.h"
#include "parse_records.c"
#include "print_records.c"

/* NOTE: sorted in record-type order */
static const recordtype parse_types[] = {
    //      type		min_rdlen		max_rdlen	parse_fn
    //      free_fn
    //      print_fn
    {0, 0, 0, NULL, NULL, NULL},
    {t_a, A_RDLEN, A_RDLEN, parse_a, free_a, print_a},
    {t_ns, MIN_NS_RDLEN, MAX_RDLEN, parse_ns, free_ns, print_ns},
    {t_cname, MIN_CNAME_RDLEN, MAX_RDLEN, parse_cname, free_cname, print_cname},
    {t_soa, MIN_SOA_RDLEN, MAX_RDLEN, parse_soa, free_soa, print_soa},
    {t_ptr, MIN_PTR_RDLEN, MAX_RDLEN, parse_ptr, free_ptr, print_ptr},
    {t_mx, MIN_MX_RDLEN, MAX_RDLEN, parse_mx, free_mx, print_mx},
    {t_txt, MIN_TXT_RDLEN, MAX_RDLEN, parse_txt, free_txt, print_txt},
    {t_aaaa, AAAA_RDLEN, AAAA_RDLEN, parse_aaaa, free_aaaa, print_aaaa},
    {t_srv, MIN_SRV_RDLEN, MAX_RDLEN, parse_srv, free_srv, print_srv},
    {t_naptr, MIN_NAPTR_RDLEN, MAX_RDLEN, parse_naptr, free_naptr, print_naptr},
    {t_opt, MIN_OPT_RDLEN, MAX_RDLEN, parse_opt, free_opt, print_opt},
    {t_caa, MIN_CAA_RDLEN, MAX_RDLEN, parse_caa, free_caa, print_caa},
    {0xFFFF, 0, 0, NULL, NULL, NULL},
};
static size_t parse_types_count = sizeof(parse_types) / sizeof(parse_types[0]);

static int type_cmp(const void *_type, const void *_recordtype) {
  dancers_rr_type type = (dancers_rr_type)_type;
  const recordtype *rt = _recordtype;

  return type - rt->type;
}

recordtype *lookup_rt(dancers_rr_type type) {
  return bsearch((void *)type, parse_types, parse_types_count,
                 sizeof(parse_types[0]), type_cmp);
}

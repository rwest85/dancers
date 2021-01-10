#include <check.h>

#include "../../include/dancers.h"
#include "fixtures.h"
#include "trace.h"

/* to test static functions: #include the C file, don't link the object */
#include "../../src/dancers.c"

static int write_parser_output = 0;

dancers_packet *cleanup_packet(dancers_packet *packet) {
  if (write_parser_output) dancers_packet_print(stderr, packet);
  dancers_packet_free(packet);
  return NULL;
}

static int test_parse_rr(const uint8_t *data, size_t *offset, size_t length,
			 dancers_rr *record) {
  char ac[65536] = {0};
  dancers_parse *parse = (dancers_parse *)ac;
  parse->header.data = data;
  parse->header.length = length;
  parse->header.offset = *offset;
  parse->header.end = (void *)parse + 65536;

  int rc = parse_rr_internal(parse, record);

  return rc;
}

void cleanup_record(void *record) {
  if (write_parser_output) {
    dancers_print_rr(stderr, record);
    fprintf(stderr, "\n");
  }
  record_clear(record);
}

START_TEST(test_parse_packet2) {
  dancers_packet *packet = NULL;

  size_t o = 42;
  int rc =
      dancers_packet_parse(__fixtures_packets_packet1_bin + o,
                           __fixtures_packets_packet1_bin_len - o, &packet);

  ck_assert_uint_eq(rc, DE_SUCCESS);
  ck_assert_ptr_ne(packet, NULL);
  ck_assert_uint_eq(packet->qid, 0xc2aa);
  ck_assert_uint_eq(packet->qr, QR_RESPONSE);
  ck_assert_uint_eq(packet->opcode, OP_QUERY);
  ck_assert_uint_eq(packet->rcode, RC_NOERROR);
  ck_assert_uint_eq(packet->aa, 1);
  ck_assert_uint_eq(packet->rd, 1);

  ck_assert_uint_eq(packet->qd_count, 1);
  dancers_rr *question = &(packet->questions[0]);
  ck_assert_str_eq(question->name, "delegation-test.ventx.de");
  ck_assert_uint_eq(question->cls, CLS_IN);
  ck_assert_uint_eq(question->type, t_ns);

  ck_assert_uint_eq(packet->an_count, 4);
  ck_assert_uint_eq(packet->answers[0].type, t_ns);

  dancers_rr_ns *ns = &(packet->answers[0].ns);
  ck_assert_str_eq(ns->ns, "ns-1527.awsdns-62.org");
  ns = &(packet->answers[1].ns);
  ck_assert_str_eq(ns->ns, "ns-1926.awsdns-48.co.uk");
  ns = &(packet->answers[2].ns);
  ck_assert_str_eq(ns->ns, "ns-282.awsdns-35.com");
  ns = &(packet->answers[3].ns);
  ck_assert_str_eq(ns->ns, "ns-670.awsdns-19.net");

  ck_assert_uint_eq(packet->ns_count, 0);

  ck_assert_uint_eq(packet->ar_count, 1);
  dancers_rr_opt *opt = &(packet->additional[0].opt);
  ck_assert_uint_eq(opt->max_udp_size, 4096);

  packet = cleanup_packet(packet);
}
END_TEST

START_TEST(test_parse_name1) {
  size_t offset = 0x36;

  char *name = parse_name(__fixtures_packets_packet1_bin, &offset,
                          __fixtures_packets_packet1_bin_len);

  ck_assert_str_eq((char *)name, "delegation-test.ventx.de");
  ck_assert_uint_eq(offset, 0x50);

  free(name);
}
END_TEST

START_TEST(test_parse_name2) {
  size_t offset = 0x60;

  char *name = parse_name(__fixtures_packets_packet1_bin, &offset,
                          __fixtures_packets_packet1_bin_len);

  ck_assert_str_eq((char *)name, "ns-1527.awsdns-62.org");
  ck_assert_uint_eq(offset, 0x77);

  free(name);
}
END_TEST

/* ALIGNMENT TEST
 *
 * confirms that the method of unpacking 4 bytes for TTL works, even when
 * misaligned test alignments 0, 2..33 (hard to test 1 so we test 9, 17, 25, 33)
 */
START_TEST(test_parse_uint32_alignment) {
  uint8_t data[128] = {0};
  uint8_t template[] = {0x00, 0x0A, 0x00, 0x01, 0xFE, 0xDC,
                        0xBA, 0x98, 0x00, 0x02, 0xCA, 0xFE};
  struct name {
    size_t len;
    uint8_t data[16];
  };

  size_t template_length = sizeof(template);

  for (size_t i = 0; i < 34; i++) {
    memset(data, 0, sizeof(data));

    data[0] = i;
    memset(data + 1, 0x41, i);

    size_t len = 1 + i;
    if (i > 0) {
      data[len++] = 0;
    }

    memcpy(data + len, template, template_length);

    size_t offset = 0;
    size_t length = len + template_length;

    dancers_rr record = {0};
    int rc = test_parse_rr(data, &offset, length, &record);

    ck_assert_uint_eq(rc, DE_SUCCESS);
    ck_assert_uint_eq(strlen(record.name), i);

    ck_assert_uint_eq(record.type, 10);
    ck_assert_uint_eq(record.cls, CLS_IN);
    ck_assert_uint_eq(record.ttl, 0xFEDCBA98);
    ck_assert_uint_eq(record.generic.rdlen, 2);
    ck_assert_ptr_ne(record.generic.rdata, NULL);

    cleanup_record(&record);
  }
}

START_TEST(test_parse_name_compressed1) {
  size_t offset = 0x0C;

  char *name = parse_name(bind_systemtest_000a60e489e7_pkt, &offset,
                          bind_systemtest_000a60e489e7_pkt_len);

  ck_assert_str_eq((char *)name, "zone000004.example");
  ck_assert_uint_eq(offset, 0x20);

  free(name);
}
END_TEST

START_TEST(test_parse_name_compressed2) {
  size_t offset = 0x30;

  char *name = parse_name(bind_systemtest_000a60e489e7_pkt, &offset,
                          bind_systemtest_000a60e489e7_pkt_len);

  ck_assert_str_eq((char *)name, "ns1.zone000004.example");
  ck_assert_uint_eq(offset, 0x36);

  free(name);
}
END_TEST

START_TEST(test_parse_packet) {
  dancers_packet *packet = NULL;
  int rc = dancers_packet_parse(bind_systemtest_000a60e489e7_pkt,
                                bind_systemtest_000a60e489e7_pkt_len, &packet);

  ck_assert_uint_eq(rc, DE_SUCCESS);
  ck_assert_ptr_ne(packet, NULL);
  ck_assert_uint_eq(packet->qid, 12594);
  ck_assert_uint_eq(packet->qr, QR_RESPONSE);
  ck_assert_uint_eq(packet->opcode, OP_QUERY);
  ck_assert_uint_eq(packet->rcode, RC_NOERROR);
  ck_assert_uint_eq(packet->aa, 1);

  ck_assert_uint_eq(packet->qd_count, 1);
  dancers_rr *question = &(packet->questions[0]);
  ck_assert_str_eq(question->name, "zone000004.example");
  ck_assert_uint_eq(question->cls, CLS_IN);
  ck_assert_uint_eq(question->type, t_soa);

  ck_assert_uint_eq(packet->an_count, 1);
  ck_assert_uint_eq(packet->answers[0].type, t_soa);
  dancers_rr_soa *soa = &(packet->answers[0].soa);
  ck_assert_str_eq(soa->name, "zone000004.example");
  ck_assert_uint_eq(soa->cls, CLS_IN);
  ck_assert_str_eq(soa->mname, "ns1.zone000004.example");
  ck_assert_str_eq(soa->rname, "");

  ck_assert_uint_eq(packet->ns_count, 2);
  ck_assert_uint_eq(packet->nameservers[0].type, t_ns);
  dancers_rr_ns *ns = &(packet->nameservers[0].ns);
  ck_assert_str_eq(ns->name, "zone000004.example");
  ck_assert_str_eq(ns->nameserver, "ns1.zone000004.example");

  ck_assert_uint_eq(packet->nameservers[1].type, t_ns);
  ns = &(packet->nameservers[1].ns);
  ck_assert_str_eq(ns->nameserver, "ns2.zone000004.example");

  ck_assert_uint_eq(packet->ar_count, 3);

  packet = cleanup_packet(packet);
}
END_TEST

START_TEST(test_parse_packet_crash1) {
  dancers_packet *packet = NULL;
  int rc = dancers_packet_parse(
      fixtures_packets_id_000000_sig_11_src_000002_op_havoc_rep_16,
      fixtures_packets_id_000000_sig_11_src_000002_op_havoc_rep_16_len,
      &packet);

  ck_assert(packet == NULL);
  ck_assert_int_eq(rc, DE_PACKET_PARSE);
}
END_TEST

START_TEST(test_parse_txt_data) {
  int rc = 0;

  dancers_rr_txt txt = {0};
  txt.type = t_txt;

  size_t offset = 0x28;
  size_t length = 0x3c;

  rc = parse_txt(fixtures_google_com_txt_response, &offset,
                 fixtures_google_com_txt_response_len, length, &txt);
  dancers_txt_contents *contents = txt.contents;

  ck_assert_int_eq(rc, DE_SUCCESS);
  ck_assert_uint_eq(contents->length, 0x3b);
  ck_assert_int_eq(contents->part_count, 1);
  ck_assert_str_eq(
      contents->data,
      "facebook-domain-verification=22rm551cu4k0ab0bxsw536tlds4h95");
  cleanup_record(&txt);
}
END_TEST

START_TEST(test_parse_txt_packet) {
  dancers_packet *packet = NULL;

  int rc = 0;

  rc = dancers_packet_parse(fixtures_google_com_txt_response,
                            fixtures_google_com_txt_response_len, &packet);

  ck_assert_int_eq(rc, DE_SUCCESS);
  ck_assert(packet != NULL);
  ck_assert_uint_eq(packet->qd_count, 1);

  ck_assert_uint_eq(packet->an_count, 5);

  ck_assert_str_eq(
      packet->answers[0].txt.contents->data,
      "facebook-domain-verification=22rm551cu4k0ab0bxsw536tlds4h95");
  ck_assert_str_eq(packet->answers[1].txt.contents->data,
                   "docusign=1b0a6754-49b1-4db5-8540-d2c12664b289");
  ck_assert_str_eq(packet->answers[2].txt.contents->data,
                   "docusign=05958488-4752-4ef2-95eb-aa7ba8a3bd0e");
  ck_assert_str_eq(
      packet->answers[3].txt.contents->data,
      "globalsign-smime-dv=CDYX+XFHUw2wml6/Gb8+59BsH31KzUr6c1l2BPvqKX8=");
  ck_assert_str_eq(packet->answers[4].txt.contents->data,
                   "v=spf1 include:_spf.google.com ~all");

  packet = cleanup_packet(packet);
}
END_TEST

START_TEST(test_parse_edns_option) {
  dancers_rr record;
  size_t offset = 0;

  int rc = test_parse_rr(option, &offset, option_len, &record);
  ck_assert_int_eq(rc, DE_SUCCESS);
}
END_TEST

START_TEST(test_parse_opt_nlnetlabs_q) {
  dancers_packet *packet = NULL;

  int rc = 0;

  rc = dancers_packet_parse(nlnetlabs_q, nlnetlabs_q_len, &packet);

  ck_assert_int_eq(rc, DE_SUCCESS);
  ck_assert_uint_eq(packet->qr, 0);

  packet = cleanup_packet(packet);
}
END_TEST

START_TEST(test_parse_opt_nlnetlabs_r) {
  dancers_packet *packet = NULL;

  int rc = 0;

  rc = dancers_packet_parse(nlnetlabs_r, nlnetlabs_r_len, &packet);

  ck_assert_int_eq(rc, DE_SUCCESS);
  ck_assert_uint_eq(packet->qr, 1);

  packet = cleanup_packet(packet);
}
END_TEST

START_TEST(test_parse_opt_probit_q) {
  dancers_packet *packet = NULL;

  int rc = 0;

  rc = dancers_packet_parse(probit_q, probit_q_len, &packet);

  ck_assert_int_eq(rc, DE_SUCCESS);
  ck_assert_uint_eq(packet->qr, 0);

  packet = cleanup_packet(packet);
}
END_TEST

START_TEST(test_parse_opt_probit_r) {
  dancers_packet *packet = NULL;

  int rc = 0;

  rc = dancers_packet_parse(probit_r, probit_r_len, &packet);

  ck_assert_int_eq(rc, DE_SUCCESS);
  ck_assert_uint_eq(packet->qr, 1);

  packet = cleanup_packet(packet);
}
END_TEST

START_TEST(test_parse_header) {
  dancers_packet packet = {0};
  size_t offset = 0;
  int rc = parse_header(fixture_header, &offset, &packet);

  ck_assert_uint_eq(rc, DE_SUCCESS);
  ck_assert_uint_eq(packet.qid, 34009);
  ck_assert_uint_eq(packet.qr, 1);
  ck_assert_uint_eq(packet.opcode, OP_QUERY);
  ck_assert_uint_eq(packet.rcode, RC_NOERROR);
  ck_assert_uint_eq(packet.aa, 1);
  ck_assert_uint_eq(packet.rd, 1);

  ck_assert_uint_eq(packet.qd_count, 1);
  ck_assert_uint_eq(packet.an_count, 5);
  ck_assert_uint_eq(packet.ns_count, 0);
  ck_assert_uint_eq(packet.ar_count, 1);
}
END_TEST

START_TEST(test_parse_naptr) {
  dancers_rr record = {0};
  dancers_rr_naptr *naptr = &(record.naptr);
  size_t offset = 0;
  int rc = test_parse_rr(fixture_naptr, &offset, fixture_naptr_len, &record);

  ck_assert_uint_eq(rc, DE_SUCCESS);
  ck_assert_str_eq(naptr->name, "example.com");
  ck_assert_uint_eq(naptr->cls, CLS_IN);
  ck_assert_uint_eq(naptr->type, t_naptr);
  ck_assert_uint_eq(naptr->ttl, 100);

  ck_assert_uint_eq(naptr->order, 100);
  ck_assert_uint_eq(naptr->preference, 10);
  ck_assert_str_eq(naptr->flags, "U");
  ck_assert_str_eq(naptr->service, "E2U+sip");
  ck_assert_str_eq(naptr->regexp, "!^.*$!sip:customer-service@example.com!");
  ck_assert_str_eq(naptr->replacement, "");

  cleanup_record(naptr);
}
END_TEST

START_TEST(test_parse_caa) {
  dancers_packet *packet = NULL;
  int rc = dancers_packet_parse(goog_caa_r, goog_caa_r_len, &packet);

  ck_assert_uint_eq(rc, DE_SUCCESS);
  ck_assert_uint_eq(packet->an_count, 1);

  dancers_rr_caa *caa = &(packet->answers[0].caa);
  ck_assert_str_eq(caa->name, "google.com");
  ck_assert_uint_eq(caa->cls, CLS_IN);
  ck_assert_uint_eq(caa->type, t_caa);
  ck_assert_uint_eq(caa->ttl, 86347);

  ck_assert_uint_eq(caa->flags, 0);
  ck_assert_str_eq(caa->tag, "issue");
  ck_assert_str_eq(caa->value, "pki.goog");

  packet = cleanup_packet(packet);
}
END_TEST

Suite *parser_suite(void) {
  Suite *s;

  char *output = getenv("CK_DANCERS_OUTPUT");
  if (output) write_parser_output = atoi(output);

  s = suite_create("Parser");

  {
    TCase *tc = tcase_create("name");
    tcase_set_tags(tc, "parser name");

    tcase_add_test(tc, test_parse_name1);
    tcase_add_test(tc, test_parse_name2);
    tcase_add_test(tc, test_parse_name_compressed1);
    tcase_add_test(tc, test_parse_name_compressed2);
    suite_add_tcase(s, tc);
  }

  {
    TCase *tc = tcase_create("edns");
    tcase_set_tags(tc, "parser rr edns");
    tcase_add_test(tc, test_parse_edns_option);
    tcase_add_test(tc, test_parse_opt_nlnetlabs_q);
    tcase_add_test(tc, test_parse_opt_nlnetlabs_r);
    tcase_add_test(tc, test_parse_opt_probit_q);
    tcase_add_test(tc, test_parse_opt_probit_r);
    suite_add_tcase(s, tc);
  }

  {
    TCase *tc = tcase_create("rr");
    tcase_set_tags(tc, "parser rr");
    tcase_add_test(tc, test_parse_uint32_alignment);
    suite_add_tcase(s, tc);
  }

  {
    TCase *tc = tcase_create("txt");
    tcase_set_tags(tc, "parser rr txt");
    tcase_add_test(tc, test_parse_txt_data);
    tcase_add_test(tc, test_parse_txt_packet);
    suite_add_tcase(s, tc);
  }

  {
    TCase *tc = tcase_create("naptr");
    tcase_set_tags(tc, "parser rr naptr");
    tcase_add_test(tc, test_parse_naptr);
    suite_add_tcase(s, tc);
  }

  {
    TCase *tc = tcase_create("caa");
    tcase_set_tags(tc, "parser rr caa");
    tcase_add_test(tc, test_parse_caa);
    suite_add_tcase(s, tc);
  }

  {
    TCase *tc = tcase_create("packet");
    tcase_set_tags(tc, "parser packet");

    tcase_add_test(tc, test_parse_packet_crash1);
    tcase_add_test(tc, test_parse_header);
    tcase_add_test(tc, test_parse_packet);
    tcase_add_test(tc, test_parse_packet2);
    suite_add_tcase(s, tc);
  }

  return s;
}

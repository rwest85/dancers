#include <check.h>

Suite *parser_suite();

int main(void) {
  int number_failed;
  SRunner *sr;

  sr = srunner_create(NULL);
  srunner_add_suite(sr, parser_suite());
  // srunner_add_suite(sr, include_suite());

  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return !(number_failed == 0);
}

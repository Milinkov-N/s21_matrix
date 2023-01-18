#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

/*
 *
 * =============== TEST CASES: s21_create_matrix ===============
 *
 */

START_TEST(tc_s21_create_matrix) {
  // matrix_t mat = {0};

  // int expect_res = OK, result_res = s21_create_matrix(3, 3, &mat);
  // ck_assert_int_eq(expect_res, result_res);

  // int expect_rows = 3, result_rows = mat.rows;
  // ck_assert_int_eq(expect_rows, result_rows);

  // int expect_columns = 3, result_columns = mat.columns;
  // ck_assert_int_eq(expect_columns, result_columns);

  // double expect_value = 0.0;
  // for (int i = 0; i < mat.rows; i++) {
  //   for (int j = 0; j < mat.columns; j++) {
  //     double result_value = mat.matrix[i][j];
  //     ck_assert_double_eq(expect_value, result_value);
  //   }
  // }
}
END_TEST

/*
 * ***********************************************************
 * ======================= TEST SUITES =======================
 * ***********************************************************
 */

Suite *ts_s21_create_matrix() {
  Suite *suite = suite_create("ts_s21_create_matrix");
  TCase *test_case = tcase_create("tc_s21_create_matrix");

  tcase_add_test(test_case, tc_s21_create_matrix);

  suite_add_tcase(suite, test_case);

  return suite;
}

int main(void) {
  Suite *test_suites[] = {ts_s21_create_matrix(),
                          // ts_s21_remove_matrix(),
                          // ts_s21_eq_matrix(),
                          // ts_s21_sum_matrix(),
                          // ts_s21_sub_matrix(),
                          // ts_s21_mult_number(),
                          // ts_s21_mult_matrix(),
                          // ts_s21_transpose(),
                          // ts_s21_calc_complements(),
                          NULL};
  int failed = 0;

  for (Suite **s = test_suites; *s != NULL; s++) {
    SRunner *runner = srunner_create(*s);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return failed;
}
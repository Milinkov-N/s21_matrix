#include <check.h>
#include <stdio.h>

#include "s21_matrix.h"

/*
 *
 * =============== TEST CASES: s21_create_matrix ===============
 *
 */

START_TEST(tc01_s21_create_matrix) {
  matrix_t mat = {0};

  int expect_res = OK, result_res = s21_create_matrix(3, 3, &mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_rows = 3, result_rows = mat.rows;
  ck_assert_int_eq(expect_rows, result_rows);

  int expect_columns = 3, result_columns = mat.columns;
  ck_assert_int_eq(expect_columns, result_columns);

  double expect_value = 0.0;
  for (int i = 0; i < mat.rows; i++) {
    for (int j = 0; j < mat.columns; j++) {
      double result_value = mat.matrix[i][j];
      ck_assert_double_eq(expect_value, result_value);
    }
  }

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(tc02_s21_create_matrix) {
  matrix_t mat = {0};

  int expect_res = ERR, result_res = s21_create_matrix(-3, 3, &mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc03_s21_create_matrix) {
  matrix_t mat = {0};

  int expect_res = ERR, result_res = s21_create_matrix(3, -3, &mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc04_s21_create_matrix) {
  matrix_t mat = {0};

  int expect_res = ERR, result_res = s21_create_matrix(-3, -3, &mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

/*
 *
 * =============== TEST CASES: s21_eq_matrix ===============
 *
 */

START_TEST(tc01_s21_eq_matrix) {
  CREATE_MATRIX(mat1, 2, 2, {{1, 2}, {3, 4}});
  CREATE_MATRIX(mat2, 2, 2, {{1, 2}, {3, 4}});

  int expect_res = SUCCESS, result_res = s21_eq_matrix(&mat1, &mat2);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc02_s21_eq_matrix) {
  CREATE_MATRIX(mat1, 2, 2, {{1.1234567, 2.1234567}, {3.1234567, 4.1234567}});
  CREATE_MATRIX(mat2, 2, 2, {{1.1234567, 2.1234567}, {3.1234567, 4.1234567}});

  int expect_res = SUCCESS, result_res = s21_eq_matrix(&mat1, &mat2);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc03_s21_eq_matrix) {
  CREATE_MATRIX(mat1, 1, 2, {{1.1234567, 2.1234567}});
  CREATE_MATRIX(mat2, 2, 2, {{1.1234567, 2.1234567}, {3.1234567, 4.1234567}});

  int expect_res = FAILURE, result_res = s21_eq_matrix(&mat1, &mat2);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc04_s21_eq_matrix) {
  matrix_t mat1 = {0}, mat2 = {0};

  s21_create_matrix(3, 3, &mat1);
  s21_create_matrix(3, 3, &mat2);

  mat1.matrix[0][0] = 1.1234568;
  mat2.matrix[0][0] = 1.1234567;

  int expect_res = FAILURE, result_res = s21_eq_matrix(&mat1, &mat2);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc05_s21_eq_matrix) {
  matrix_t mat1 = {0}, mat2 = {0};

  int expect_res = FAILURE, result_res = s21_eq_matrix(&mat1, &mat2);
  ck_assert_int_eq(expect_res, result_res);
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

  tcase_add_test(test_case, tc01_s21_create_matrix);
  tcase_add_test(test_case, tc02_s21_create_matrix);
  tcase_add_test(test_case, tc03_s21_create_matrix);
  tcase_add_test(test_case, tc04_s21_create_matrix);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_s21_eq_matrix() {
  Suite *suite = suite_create("ts_s21_eq_matrix");
  TCase *test_case = tcase_create("tc_s21_eq_matrix");

  tcase_add_test(test_case, tc01_s21_eq_matrix);
  tcase_add_test(test_case, tc02_s21_eq_matrix);
  tcase_add_test(test_case, tc03_s21_eq_matrix);
  tcase_add_test(test_case, tc04_s21_eq_matrix);
  tcase_add_test(test_case, tc05_s21_eq_matrix);

  suite_add_tcase(suite, test_case);

  return suite;
}

int main(void) {
  Suite *test_suites[] = {ts_s21_create_matrix(), ts_s21_eq_matrix(),
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
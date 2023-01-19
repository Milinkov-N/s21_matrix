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

START_TEST(tc05_s21_create_matrix) {
  int expect_res = ERR, result_res = s21_create_matrix(3, 3, NULL);
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

START_TEST(tc06_s21_eq_matrix) {
  matrix_t mat = {0};

  int expect_res = FAILURE, result_res = s21_eq_matrix(NULL, &mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc07_s21_eq_matrix) {
  matrix_t mat = {0};

  int expect_res = FAILURE, result_res = s21_eq_matrix(&mat, NULL);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc08_s21_eq_matrix) {
  int expect_res = FAILURE, result_res = s21_eq_matrix(NULL, NULL);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

/*
 *
 * =============== TEST CASES: s21_sum_matrix ===============
 *
 */

START_TEST(tc01_s21_sum_matrix) {
  CREATE_MATRIX(mat1, 1, 1, {{14}});
  CREATE_MATRIX(mat2, 1, 1, {{23}});
  CREATE_MATRIX(exp_mat, 1, 1, {{37}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_sum_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc02_s21_sum_matrix) {
  CREATE_MATRIX(mat1, 2, 2, {{14, 43}, {-5, 12.47}});
  CREATE_MATRIX(mat2, 2, 2, {{23, -12.51}, {50, 0}});
  CREATE_MATRIX(exp_mat, 2, 2, {{37, 30.49}, {45, 12.47}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_sum_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc03_s21_sum_matrix) {
  CREATE_MATRIX(mat1, 3, 3,
                {{0, 13, -4}, {-5, 17.357, 400}, {321.5672, -0.001, 2.5}});
  CREATE_MATRIX(mat2, 3, 3,
                {{15.5, -12.51, 99.98},
                 {521.125, 0.34, 0.019855},
                 {516.301, 10, -11.12}});
  CREATE_MATRIX(exp_mat, 3, 3,
                {{15.5, 0.49, 95.98},
                 {516.125, 17.697, 400.019855},
                 {837.8682, 9.999, -8.62}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_sum_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc04_s21_sum_matrix) {
  CREATE_MATRIX(mat1, 4, 4,
                {{0, 13, -4, 1},
                 {-5, 17.357, 400, 88.80},
                 {321.5672, -0.001, 2.5, 75.75},
                 {0.005001, 1, 36.6, 420.18}});
  CREATE_MATRIX(mat2, 4, 4,
                {{15.5, -12.51, 99.98, 0},
                 {521.125, 0.34, 0.019855, 7},
                 {516.301, 10, -11.12, -9},
                 {5, 17.18, -4, 55.56}});
  CREATE_MATRIX(exp_mat, 4, 4,
                {{15.5, 0.49, 95.98, 1},
                 {516.125, 17.697, 400.019855, 95.8},
                 {837.8682, 9.999, -8.62, 66.75},
                 {5.005001, 18.18, 32.6, 475.74}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_sum_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc05_s21_sum_matrix) {
  CREATE_MATRIX(mat1, 4, 4,
                {{0, 13, -4, 1},
                 {-5, 17.357, 400, 88.80},
                 {321.5672, -0.001, 2.5, 75.75},
                 {0.005001, 1, 36.6, 420.18}});
  CREATE_MATRIX(mat2, 2, 4,
                {{15.5, -12.51, 99.98, 0}, {521.125, 0.34, 0.019855, 7}});

  matrix_t res_mat = {0};

  int expect_res = CALC_ERR,
      result_res = s21_sum_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc06_s21_sum_matrix) {
  CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
  CREATE_MATRIX(mat2, 2, 4,
                {{15.5, -12.51, 99.98, 0}, {521.125, 0.34, 0.019855, 7}});

  matrix_t res_mat = {0};

  int expect_res = CALC_ERR,
      result_res = s21_sum_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc07_s21_sum_matrix) {
  CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
  CREATE_MATRIX(mat2, 3, 4,
                {{15.5, -12.51, 99.98, 0},
                 {521.125, 0.34, 0.019855, 7},
                 {521.125, 0.34, 0.019855, 7}});

  matrix_t res_mat = {0};

  int expect_res = CALC_ERR,
      result_res = s21_sum_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc08_s21_sum_matrix) {
  matrix_t mat1 = {0}, mat2 = {0}, res_mat = {0};

  int expect_res = ERR, result_res = s21_sum_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

/*
 *
 * =============== TEST CASES: s21_sub_matrix ===============
 *
 */

START_TEST(tc01_s21_sub_matrix) {
  CREATE_MATRIX(mat1, 1, 1, {{14}});
  CREATE_MATRIX(mat2, 1, 1, {{23}});
  CREATE_MATRIX(exp_mat, 1, 1, {{-9}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_sub_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc02_s21_sub_matrix) {
  CREATE_MATRIX(mat1, 2, 2, {{14, 43}, {-5, 12.47}});
  CREATE_MATRIX(mat2, 2, 2, {{23, -12.51}, {50, 0}});
  CREATE_MATRIX(exp_mat, 2, 2, {{-9, 55.51}, {-55, 12.47}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_sub_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc03_s21_sub_matrix) {
  CREATE_MATRIX(mat1, 3, 3,
                {{0, 13, -4}, {-5, 17.357, 400}, {321.5672, -0.001, 2.5}});
  CREATE_MATRIX(mat2, 3, 3,
                {{15.5, -12.51, 99.98},
                 {521.125, 0.34, 0.019855},
                 {516.301, 10, -11.12}});
  CREATE_MATRIX(exp_mat, 3, 3,
                {{-15.5, 25.51, -103.98},
                 {-526.125, 17.017, 399.980145},
                 {-194.7338, -10.001, 13.62}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_sub_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc04_s21_sub_matrix) {
  CREATE_MATRIX(mat1, 4, 4,
                {{0, 13, -4, 1},
                 {-5, 17.357, 400, 88.80},
                 {321.5672, -0.001, 2.5, 75.75},
                 {0.005001, 1, 36.6, 420.18}});
  CREATE_MATRIX(mat2, 4, 4,
                {{15.5, -12.51, 99.98, 0},
                 {521.125, 0.34, 0.019855, 7},
                 {516.301, 10, -11.12, -9},
                 {5, 17.18, -4, 55.56}});
  CREATE_MATRIX(exp_mat, 4, 4,
                {{-15.5, 25.51, -103.98, 1},
                 {-526.125, 17.017, 399.980145, 81.8},
                 {-194.7338, -10.001, 13.62, 84.75},
                 {-4.994999, -16.18, 40.6, 364.62}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_sub_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc05_s21_sub_matrix) {
  CREATE_MATRIX(mat1, 4, 4,
                {{0, 13, -4, 1},
                 {-5, 17.357, 400, 88.80},
                 {321.5672, -0.001, 2.5, 75.75},
                 {0.005001, 1, 36.6, 420.18}});
  CREATE_MATRIX(mat2, 2, 4,
                {{15.5, -12.51, 99.98, 0}, {521.125, 0.34, 0.019855, 7}});

  matrix_t res_mat = {0};

  int expect_res = CALC_ERR,
      result_res = s21_sub_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc06_s21_sub_matrix) {
  CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
  CREATE_MATRIX(mat2, 2, 4,
                {{15.5, -12.51, 99.98, 0}, {521.125, 0.34, 0.019855, 7}});

  matrix_t res_mat = {0};

  int expect_res = CALC_ERR,
      result_res = s21_sub_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc07_s21_sub_matrix) {
  CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
  CREATE_MATRIX(mat2, 3, 4,
                {{15.5, -12.51, 99.98, 0},
                 {521.125, 0.34, 0.019855, 7},
                 {521.125, 0.34, 0.019855, 7}});

  matrix_t res_mat = {0};

  int expect_res = CALC_ERR,
      result_res = s21_sub_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc08_s21_sub_matrix) {
  matrix_t mat1 = {0}, mat2 = {0}, res_mat = {0};

  int expect_res = ERR, result_res = s21_sub_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
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
  tcase_add_test(test_case, tc05_s21_create_matrix);

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
  tcase_add_test(test_case, tc06_s21_eq_matrix);
  tcase_add_test(test_case, tc07_s21_eq_matrix);
  tcase_add_test(test_case, tc08_s21_eq_matrix);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_s21_sum_matrix() {
  Suite *suite = suite_create("ts_s21_sum_matrix");
  TCase *test_case = tcase_create("tc_s21_sum_matrix");

  tcase_add_test(test_case, tc01_s21_sum_matrix);
  tcase_add_test(test_case, tc02_s21_sum_matrix);
  tcase_add_test(test_case, tc03_s21_sum_matrix);
  tcase_add_test(test_case, tc04_s21_sum_matrix);
  tcase_add_test(test_case, tc05_s21_sum_matrix);
  tcase_add_test(test_case, tc06_s21_sum_matrix);
  tcase_add_test(test_case, tc07_s21_sum_matrix);
  tcase_add_test(test_case, tc08_s21_sum_matrix);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_s21_sub_matrix() {
  Suite *suite = suite_create("ts_s21_sub_matrix");
  TCase *test_case = tcase_create("tc_s21_sub_matrix");

  tcase_add_test(test_case, tc01_s21_sub_matrix);
  tcase_add_test(test_case, tc02_s21_sub_matrix);
  tcase_add_test(test_case, tc03_s21_sub_matrix);
  tcase_add_test(test_case, tc04_s21_sub_matrix);
  tcase_add_test(test_case, tc05_s21_sub_matrix);
  tcase_add_test(test_case, tc06_s21_sub_matrix);
  tcase_add_test(test_case, tc07_s21_sub_matrix);
  tcase_add_test(test_case, tc08_s21_sub_matrix);

  suite_add_tcase(suite, test_case);

  return suite;
}

int main(void) {
  Suite *test_suites[] = {ts_s21_create_matrix(), ts_s21_eq_matrix(),
                          ts_s21_sum_matrix(), ts_s21_sub_matrix(),
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

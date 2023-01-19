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

START_TEST(tc09_s21_sum_matrix) {
  CREATE_MATRIX(mat1, 3, 3,
                {{0, 13, -4}, {-5, 17.357, 400}, {321.5672, -0.001, 2.5}});
  CREATE_MATRIX(mat2, 3, 3,
                {{15.5, -12.51, 99.98},
                 {521.125, 0.34, 0.019855},
                 {516.301, 10, -11.12}});

  int expect_res = ERR, result_res = s21_sum_matrix(&mat1, &mat2, NULL);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc10_s21_sum_matrix) {
  matrix_t res_mat = {0};

  int expect_res = ERR, result_res = s21_sum_matrix(NULL, NULL, &res_mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc11_s21_sum_matrix) {
  int expect_res = ERR, result_res = s21_sum_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(expect_res, result_res);
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

START_TEST(tc09_s21_sub_matrix) {
  CREATE_MATRIX(mat1, 3, 3,
                {{0, 13, -4}, {-5, 17.357, 400}, {321.5672, -0.001, 2.5}});
  CREATE_MATRIX(mat2, 3, 3,
                {{15.5, -12.51, 99.98},
                 {521.125, 0.34, 0.019855},
                 {516.301, 10, -11.12}});

  int expect_res = ERR, result_res = s21_sub_matrix(&mat1, &mat2, NULL);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc10_s21_sub_matrix) {
  matrix_t res_mat = {0};

  int expect_res = ERR, result_res = s21_sub_matrix(NULL, NULL, &res_mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc11_s21_sub_matrix) {
  int expect_res = ERR, result_res = s21_sub_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

/*
 *
 * =============== TEST CASES: s21_mult_number ===============
 *
 */

START_TEST(tc01_s21_mult_number) {
  CREATE_MATRIX(mat1, 1, 1, {{14}});
  CREATE_MATRIX(exp_mat, 1, 1, {{70}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_number(&mat1, 5, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc02_s21_mult_number) {
  CREATE_MATRIX(mat1, 2, 2, {{14, 5.05}, {70, 23.12}});
  CREATE_MATRIX(exp_mat, 2, 2, {{42.238, 15.23585}, {211.19, 69.75304}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_number(&mat1, 3.017, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc03_s21_mult_number) {
  CREATE_MATRIX(mat1, 3, 3,
                {{14, 5.05, -10}, {70, 23.12, -22.23}, {0, 35.1, 7}});
  CREATE_MATRIX(exp_mat, 3, 3,
                {{-14.14, -5.1005, 10.1},
                 {-70.7, -23.3512, 22.4523},
                 {0, -35.451, -7.07}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_number(&mat1, -1.01, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc04_s21_mult_number) {
  CREATE_MATRIX(mat1, 4, 4,
                {{14, 5.05, -10, 101},
                 {70, 23.12, -22.23, 220.1},
                 {0, 35.1, 7, 95.420},
                 {0.054, 1, -13, 17.18}});
  CREATE_MATRIX(exp_mat, 4, 4,
                {{28.0448, 10.11616, -20.032, 202.3232},
                 {140.224, 46.313984, -44.531136, 440.90432},
                 {0, 70.31232, 14.0224, 191.145344},
                 {0.1081728, 2.0032, -26.0416, 34.414976}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_number(&mat1, 2.0032, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc05_s21_mult_number) {
  CREATE_MATRIX(mat1, 1, 4, {{14, 5.05, -10, 101}});
  CREATE_MATRIX(exp_mat, 1, 4, {{28.0448, 10.11616, -20.032, 202.3232}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_number(&mat1, 2.0032, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc06_s21_mult_number) {
  CREATE_MATRIX(mat1, 4, 1, {{14}, {5.05}, {-10}, {101}});
  CREATE_MATRIX(exp_mat, 4, 1, {{28.0448}, {10.11616}, {-20.032}, {202.3232}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_number(&mat1, 2.0032, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc07_s21_mult_number) {
  matrix_t mat1 = {0}, res_mat = {0};

  int expect_res = ERR, result_res = s21_mult_number(&mat1, 2.0032, &res_mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc08_s21_mult_number) {
  matrix_t res_mat = {0};

  int expect_res = ERR, result_res = s21_mult_number(NULL, 2.0032, &res_mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc09_s21_mult_number) {
  CREATE_MATRIX(mat1, 4, 1, {{14}, {5.05}, {-10}, {101}});

  int expect_res = ERR, result_res = s21_mult_number(&mat1, 2.0032, NULL);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(tc10_s21_mult_number) {
  int expect_res = ERR, result_res = s21_mult_number(NULL, 2.0032, NULL);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

/*
 *
 * =============== TEST CASES: s21_mult_matrix ===============
 *
 */

START_TEST(tc01_s21_mult_matrix) {
  CREATE_MATRIX(mat1, 1, 1, {{14}});
  CREATE_MATRIX(mat2, 1, 1, {{4}});
  CREATE_MATRIX(exp_mat, 1, 1, {{56}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_matrix(&mat1, &mat2, &res_mat);
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

START_TEST(tc02_s21_mult_matrix) {
  CREATE_MATRIX(mat1, 2, 2, {{14, 12.456}, {-3, 0}});
  CREATE_MATRIX(mat2, 2, 2, {{4, -18}, {10, 5}});
  CREATE_MATRIX(exp_mat, 2, 2, {{180.56, -189.72}, {-12, 54}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_matrix(&mat1, &mat2, &res_mat);
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

START_TEST(tc03_s21_mult_matrix) {
  CREATE_MATRIX(mat1, 3, 3, {{14, 12.456, -1}, {-3, 0, 13}, {4.04, -80, 6}});
  CREATE_MATRIX(mat2, 3, 3, {{4, -18, 7.07}, {10, 5, 6}, {20, 0, 420}});
  CREATE_MATRIX(exp_mat, 3, 3,
                {{160.56, -189.72, -246.284},
                 {248, 54, 5438.79},
                 {-663.84, -472.72, 2068.5628}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_matrix(&mat1, &mat2, &res_mat);
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

START_TEST(tc04_s21_mult_matrix) {
  CREATE_MATRIX(mat1, 4, 4,
                {{14, 12.456, -1, 5},
                 {-3, 0, 13, -10},
                 {4.04, -80, 6, 56},
                 {0.001, -2.5, 3.6, 0.7983}});
  CREATE_MATRIX(
      mat2, 4, 4,
      {{4, -18, 7.07, 1}, {10, 5, 6, 2}, {20, 0, 420, 1}, {0, 30, 7.78, -12}});
  CREATE_MATRIX(exp_mat, 4, 4,
                {{160.56, -39.72, -207.384, -22.088},
                 {248, -246, 5360.99, 130},
                 {-663.84, 1207.28, 2504.2428, -821.96},
                 {47.004, 11.431, 1503.217844, -10.9786}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_matrix(&mat1, &mat2, &res_mat);
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

START_TEST(tc05_s21_mult_matrix) {
  CREATE_MATRIX(mat1, 2, 4, {{14, 12.456, -1, 5}, {-3, 0, 13, -10}});
  CREATE_MATRIX(mat2, 4, 2, {{4, -18}, {10, 5}, {20, 0}, {0, 30}});
  CREATE_MATRIX(exp_mat, 2, 2, {{160.56, -39.72}, {248, -246}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_matrix(&mat1, &mat2, &res_mat);
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

START_TEST(tc06_s21_mult_matrix) {
  CREATE_MATRIX(mat1, 3, 1, {{14}, {-3}, {4.04}});
  CREATE_MATRIX(mat2, 1, 3, {{4, -18, 7.07}});
  CREATE_MATRIX(
      exp_mat, 3, 3,
      {{56, -252, 98.98}, {-12, 54, -21.21}, {16.16, -72.72, 28.5628}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_mult_matrix(&mat1, &mat2, &res_mat);
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

START_TEST(tc07_s21_mult_matrix) {
  CREATE_MATRIX(mat1, 3, 1, {{14}, {-3}, {4.04}});
  CREATE_MATRIX(mat2, 1, 3, {{4, 0.0 / 0.0, 7.07}});

  matrix_t res_mat = {0};

  int expect_res = CALC_ERR,
      result_res = s21_mult_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc08_s21_mult_matrix) {
  CREATE_MATRIX(mat1, 3, 1, {{14}, {-3}, {4.04}});
  CREATE_MATRIX(mat2, 1, 3, {{4, 0, 7.07}});

  int expect_res = ERR, result_res = s21_mult_matrix(&mat1, &mat2, NULL);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&mat2);
}
END_TEST

START_TEST(tc09_s21_mult_matrix) {
  matrix_t mat1 = {0}, mat2 = {0}, res_mat = {0};

  int expect_res = ERR, result_res = s21_mult_matrix(&mat1, &mat2, &res_mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc10_s21_mult_matrix) {
  matrix_t res_mat = {0};

  int expect_res = ERR, result_res = s21_mult_matrix(NULL, NULL, &res_mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc11_s21_mult_matrix) {
  int expect_res = ERR, result_res = s21_mult_matrix(NULL, NULL, NULL);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

/*
 *
 * =============== TEST CASES: s21_transpose ===============
 *
 */

START_TEST(tc01_s21_transpose) {
  CREATE_MATRIX(mat1, 1, 1, {{14}});
  CREATE_MATRIX(exp_mat, 1, 1, {{14}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_transpose(&mat1, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc02_s21_transpose) {
  CREATE_MATRIX(mat1, 2, 2, {{14, 15}, {-1, 0}});
  CREATE_MATRIX(exp_mat, 2, 2, {{14, -1}, {15, 0}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_transpose(&mat1, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc03_s21_transpose) {
  CREATE_MATRIX(mat1, 3, 3, {{14, 15, -2}, {0, 50, 3}, {17, -0.001, 6}});
  CREATE_MATRIX(exp_mat, 3, 3, {{14, 0, 17}, {15, 50, -0.001}, {-2, 3, 6}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_transpose(&mat1, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc04_s21_transpose) {
  CREATE_MATRIX(mat1, 2, 4, {{14, 15, -2, 90}, {0, 50, 3, 10}});
  CREATE_MATRIX(exp_mat, 4, 2, {{14, 0}, {15, 50}, {-2, 3}, {90, 10}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_transpose(&mat1, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc05_s21_transpose) {
  CREATE_MATRIX(mat1, 3, 1, {{14}, {3}, {0}});
  CREATE_MATRIX(exp_mat, 1, 3, {{14, 3, 0}});

  matrix_t res_mat = {0};

  int expect_res = OK, result_res = s21_transpose(&mat1, &res_mat);
  ck_assert_int_eq(expect_res, result_res);

  int expect_mat_eq = SUCCESS,
      result_mat_eq = s21_eq_matrix(&exp_mat, &res_mat);
  ck_assert_int_eq(expect_mat_eq, result_mat_eq);

  s21_remove_matrix(&mat1);
  s21_remove_matrix(&exp_mat);
  s21_remove_matrix(&res_mat);
}
END_TEST

START_TEST(tc06_s21_transpose) {
  matrix_t mat = {0}, res_mat = {0};
  int expect_res = ERR, result_res = s21_transpose(&mat, &res_mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc07_s21_transpose) {
  CREATE_MATRIX(mat1, 3, 1, {{14}, {3}, {0}});

  int expect_res = ERR, result_res = s21_transpose(&mat1, NULL);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat1);
}
END_TEST

START_TEST(tc08_s21_transpose) {
  matrix_t res_mat = {0};

  int expect_res = ERR, result_res = s21_transpose(NULL, &res_mat);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc09_s21_transpose) {
  int expect_res = ERR, result_res = s21_transpose(NULL, NULL);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

/*
 *
 * =============== TEST CASES: s21_determinant ===============
 *
 */

START_TEST(tc01_s21_determinant) {
  CREATE_MATRIX(mat, 1, 1, {{14}});
  double exp_val = 14, res_val = 0;

  int expect_res = OK, result_res = s21_determinant(&mat, &res_val);
  ck_assert_int_eq(expect_res, result_res);
  ck_assert_double_eq(exp_val, res_val);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(tc02_s21_determinant) {
  CREATE_MATRIX(mat, 2, 2, {{4, 1}, {0, 9}});
  double exp_val = 36, res_val = 0;

  int expect_res = OK, result_res = s21_determinant(&mat, &res_val);
  ck_assert_int_eq(expect_res, result_res);
  ck_assert_double_eq(exp_val, res_val);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(tc03_s21_determinant) {
  CREATE_MATRIX(mat, 3, 3, {{4, 1, 2.5}, {0, 9, 7.1}, {0.001, 0, 0}});
  double exp_val = -0.0154, res_val = 0;

  int expect_res = OK, result_res = s21_determinant(&mat, &res_val);
  ck_assert_int_eq(expect_res, result_res);
  ck_assert_double_eq_tol(exp_val, res_val, 1e-6);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(tc04_s21_determinant) {
  CREATE_MATRIX(mat, 4, 4,
                {{4, 1, 2.5, 3},
                 {0, 9, 7.1, -2},
                 {0.001, 0, 0, 5},
                 {0, 25.568, 30, -40.95}});
  double exp_val = -1768.5158084, res_val = 0;

  int expect_res = OK, result_res = s21_determinant(&mat, &res_val);
  ck_assert_int_eq(expect_res, result_res);
  ck_assert_double_eq_tol(exp_val, res_val, 1e-7);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(tc05_s21_determinant) {
  CREATE_MATRIX(mat, 4, 4,
                {{4, 1, 2.5, 3},
                 {0, 9, 7.1, -2},
                 {0.001, 0, 0, 5},
                 {0, 25.568, 30, -40.95}});

  int expect_res = ERR, result_res = s21_determinant(&mat, NULL);
  ck_assert_int_eq(expect_res, result_res);

  s21_remove_matrix(&mat);
}
END_TEST

START_TEST(tc06_s21_determinant) {
  double res_val = 0;

  int expect_res = ERR, result_res = s21_determinant(NULL, &res_val);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc07_s21_determinant) {
  int expect_res = ERR, result_res = s21_determinant(NULL, NULL);
  ck_assert_int_eq(expect_res, result_res);
}
END_TEST

START_TEST(tc08_s21_determinant) {
  matrix_t mat = {0};
  double res_val = 0;

  int expect_res = ERR, result_res = s21_determinant(&mat, &res_val);
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
  tcase_add_test(test_case, tc09_s21_sum_matrix);
  tcase_add_test(test_case, tc10_s21_sum_matrix);
  tcase_add_test(test_case, tc11_s21_sum_matrix);

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
  tcase_add_test(test_case, tc09_s21_sub_matrix);
  tcase_add_test(test_case, tc10_s21_sub_matrix);
  tcase_add_test(test_case, tc11_s21_sub_matrix);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_s21_mult_number() {
  Suite *suite = suite_create("ts_s21_mult_number");
  TCase *test_case = tcase_create("tc_s21_mult_number");

  tcase_add_test(test_case, tc01_s21_mult_number);
  tcase_add_test(test_case, tc02_s21_mult_number);
  tcase_add_test(test_case, tc03_s21_mult_number);
  tcase_add_test(test_case, tc04_s21_mult_number);
  tcase_add_test(test_case, tc05_s21_mult_number);
  tcase_add_test(test_case, tc06_s21_mult_number);
  tcase_add_test(test_case, tc07_s21_mult_number);
  tcase_add_test(test_case, tc08_s21_mult_number);
  tcase_add_test(test_case, tc09_s21_mult_number);
  tcase_add_test(test_case, tc10_s21_mult_number);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_s21_mult_matrix() {
  Suite *suite = suite_create("ts_s21_mult_matrix");
  TCase *test_case = tcase_create("tc_s21_mult_matrix");

  tcase_add_test(test_case, tc01_s21_mult_matrix);
  tcase_add_test(test_case, tc02_s21_mult_matrix);
  tcase_add_test(test_case, tc03_s21_mult_matrix);
  tcase_add_test(test_case, tc04_s21_mult_matrix);
  tcase_add_test(test_case, tc05_s21_mult_matrix);
  tcase_add_test(test_case, tc06_s21_mult_matrix);
  tcase_add_test(test_case, tc07_s21_mult_matrix);
  tcase_add_test(test_case, tc08_s21_mult_matrix);
  tcase_add_test(test_case, tc09_s21_mult_matrix);
  tcase_add_test(test_case, tc10_s21_mult_matrix);
  tcase_add_test(test_case, tc11_s21_mult_matrix);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_s21_transpose() {
  Suite *suite = suite_create("ts_s21_transpose");
  TCase *test_case = tcase_create("tc_s21_transpose");

  tcase_add_test(test_case, tc01_s21_transpose);
  tcase_add_test(test_case, tc02_s21_transpose);
  tcase_add_test(test_case, tc03_s21_transpose);
  tcase_add_test(test_case, tc04_s21_transpose);
  tcase_add_test(test_case, tc05_s21_transpose);
  tcase_add_test(test_case, tc06_s21_transpose);
  tcase_add_test(test_case, tc07_s21_transpose);
  tcase_add_test(test_case, tc08_s21_transpose);
  tcase_add_test(test_case, tc09_s21_transpose);

  suite_add_tcase(suite, test_case);

  return suite;
}

Suite *ts_s21_determinant() {
  Suite *suite = suite_create("ts_s21_determinant");
  TCase *test_case = tcase_create("tc_s21_determinant");

  tcase_add_test(test_case, tc01_s21_determinant);
  tcase_add_test(test_case, tc02_s21_determinant);
  tcase_add_test(test_case, tc03_s21_determinant);
  tcase_add_test(test_case, tc04_s21_determinant);
  tcase_add_test(test_case, tc05_s21_determinant);
  tcase_add_test(test_case, tc06_s21_determinant);
  tcase_add_test(test_case, tc07_s21_determinant);
  tcase_add_test(test_case, tc08_s21_determinant);

  suite_add_tcase(suite, test_case);

  return suite;
}

int main(void) {
  Suite *test_suites[] = {ts_s21_create_matrix(), ts_s21_eq_matrix(),
                          ts_s21_sum_matrix(), ts_s21_sub_matrix(),
                          ts_s21_mult_number(), ts_s21_mult_matrix(),
                          ts_s21_transpose(),
                          // ts_s21_calc_complements(),
                          ts_s21_determinant(), NULL};
  int failed = 0;

  for (Suite **s = test_suites; *s != NULL; s++) {
    SRunner *runner = srunner_create(*s);
    srunner_run_all(runner, CK_NORMAL);
    failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  return failed;
}

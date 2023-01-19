#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>  // to delete
#include <stdlib.h>

#define OK 0
#define ERR 1
#define CALC_ERR 2

#define SUCCESS 1
#define FAILURE 0

#define CREATE_MATRIX(_NAME_, _ROWS_, _COLUMNS_, ...)                   \
  double __##_NAME_##_init_array[_ROWS_][_COLUMNS_] = __VA_ARGS__;      \
  matrix_t _NAME_ = {0};                                                \
  int __##_NAME_##_res = s21_create_matrix(_ROWS_, _COLUMNS_, &_NAME_); \
  if (__##_NAME_##_res != ERR)                                          \
    for (int i = 0; i < _NAME_.rows; i++)                               \
      for (int j = 0; j < _NAME_.columns; j++)                          \
        _NAME_.matrix[i][j] = __##_NAME_##_init_array[i][j];

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);

void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/*
 * =============== UTILITY FUNCTIONS ===============
 */

int arith_wrapper(matrix_t *A, matrix_t *B, matrix_t *result,
                  void (*cb)(double *, double *, double *));

void arith_sum(double *lhs, double *rhs, double *res);

void arith_sub(double *lhs, double *rhs, double *res);

int determinant_inner(matrix_t *A, double *result);

int submatrix_of(int row, int column, matrix_t *A, matrix_t *result);

int eq_matrix_dim(matrix_t *A, matrix_t *B);

int calc_minor_matrix(matrix_t *A, double *result);

void print_matrix(matrix_t *A);

int is_init(matrix_t *A);

int is_nan(double x);

void free_2d_array(double **arr, int height);

#endif  // SRC_S21_MATRIX_H_

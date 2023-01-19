#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = ERR;

  if (result != NULL && rows > 0 && columns > 0) {
    if ((result->matrix = calloc(rows, sizeof(double *))) != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) break;
        if (i == rows - 1) res = OK;
      }

      if (res == OK) {
        result->rows = rows;
        result->columns = columns;
      } else {
        free_2d_array(result->matrix, rows);
        result->matrix = NULL;
      }
    }
  }

  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    free_2d_array(A->matrix, A->rows);
    A->rows = 0;
    A->columns = 0;
    A->matrix = NULL;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = FAILURE;

  if (eq_matrix_dim(A, B)) {
    res = SUCCESS;
    for (int i = 0; res && i < A->rows; i++)
      for (int j = 0; res && j < A->columns; j++)
        if (A->matrix[i] == NULL || B->matrix[i] == NULL ||
            fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7)
          res = FAILURE;
  }

  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return arith_wrapper(A, B, result, arith_sum);
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return arith_wrapper(A, B, result, arith_sub);
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = ERR;

  if (is_init(A)) {
    res = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; res == OK && i < A->rows; i++)
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        if (is_nan(result->matrix[i][j])) res = CALC_ERR;
      }
    if (res == CALC_ERR) s21_remove_matrix(result);
  }

  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = ERR;

  if (is_init(A) && is_init(B)) {
    res = CALC_ERR;

    if (A->columns == B->rows) {
      res = s21_create_matrix(A->rows, B->columns, result);

      for (int i = 0; res == OK && i < A->rows; i++)
        for (int j = 0; j < B->columns; j++)
          for (int k = 0; k < B->rows; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
            if (is_nan(result->matrix[i][j])) res = CALC_ERR;
          }

      if (res == CALC_ERR) s21_remove_matrix(result);
    }
  }

  return res;
}

/*
 *
 * =============== UTILITY FUNCTIONS ===============
 *
 */

int arith_wrapper(matrix_t *A, matrix_t *B, matrix_t *result,
                  void (*cb)(double *, double *, double *)) {
  int res = ERR;

  if (is_init(A) && is_init(B)) {
    res = CALC_ERR;

    if (eq_matrix_dim(A, B)) {
      res = s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; res == OK && i < A->rows; i++)
        for (int j = 0; j < A->columns; j++) {
          cb(&A->matrix[i][j], &B->matrix[i][j], &result->matrix[i][j]);
          if (is_nan(result->matrix[i][j])) res = CALC_ERR;
        }
      if (res == CALC_ERR) s21_remove_matrix(result);
    }
  }

  return res;
}

void arith_sum(double *lhs, double *rhs, double *res) { *res = *lhs + *rhs; }

void arith_sub(double *lhs, double *rhs, double *res) { *res = *lhs - *rhs; }

int eq_matrix_dim(matrix_t *A, matrix_t *B) {
  int res = FAILURE;

  if (is_init(A) && is_init(B))
    if (A->rows == B->rows && A->columns == B->columns) res = SUCCESS;

  return res;
}

int is_init(matrix_t *A) {
  return A != NULL && A->matrix != NULL && A->rows > 0 && A->columns > 0;
}

int is_nan(double x) { return x != x; }

void print_matrix(matrix_t *A) {
  if (A != NULL) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) printf("%lf ", A->matrix[i][j]);
      printf("\n");
    }
  }
}

void free_2d_array(double **arr, int height) {
  if (arr != NULL) {
    for (int i = 0; i < height; i++)
      if (arr[i] != NULL) free(arr[i]);
    free(arr);
  }
}

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

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = ERR;

  if (is_init(A) && result != NULL) {
    res = s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; res == OK && i < A->rows; i++)
      for (int j = 0; j < A->columns; j++)
        result->matrix[j][i] = A->matrix[i][j];
  }

  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = ERR;

  if (is_init(A) && result != NULL) {
    res = CALC_ERR;

    if (A->rows == A->columns && A->rows > 1) {
      res = s21_create_matrix(A->rows, A->columns, result);

      for (int i = 0; res == OK && i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor = {0};
          double dtmt = 0;

          if ((res = submatrix_of(i, j, A, &minor)) == OK) {
            if ((res = s21_determinant(&minor, &dtmt)) == OK)
              result->matrix[i][j] = dtmt * pow(-1, i + j);
            s21_remove_matrix(&minor);
          }
        }
      }
    }
  }

  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = ERR;

  if (is_init(A) && result != NULL) {
    res = CALC_ERR;

    if (A->rows == A->columns) {
      res = OK;
      if (A->rows == 1)
        *result = A->matrix[0][0];
      else
        res = determinant_inner(A, result);
    }
  }

  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = ERR;

  if (is_init(A) && result != NULL) {
    double dtmt = 0;
    res = s21_determinant(A, &dtmt);

    if (res == OK && dtmt == 0) res = CALC_ERR;

    if (res == OK && A->rows == 1) {
      res = s21_mult_number(A, 1 / A->matrix[0][0] / A->matrix[0][0], result);
    } else if (res == OK) {
      matrix_t alg_comp = {0};

      if ((res = s21_calc_complements(A, &alg_comp)) == OK) {
        res = s21_transpose(&alg_comp, result);
        s21_remove_matrix(&alg_comp);
      }
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

int determinant_inner(matrix_t *A, double *result) {
  int res = OK;

  if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    for (int i = 0; i < A->rows; i++) {
      matrix_t minor = {0};

      if ((res = submatrix_of(0, i, A, &minor)) == OK) {
        double temp = 0;

        if ((res = determinant_inner(&minor, &temp)) == OK)
          *result += pow(-1, i) * A->matrix[0][i] * temp;

        s21_remove_matrix(&minor);
      }
    }
  }

  return res;
}

int submatrix_of(int row, int column, matrix_t *A, matrix_t *result) {
  int res = ERR;

  if (is_init(A) && result != NULL) {
    res = s21_create_matrix(A->rows - 1, A->columns - 1, result);

    if (res == OK) {
      int idx = 0, jdx = 0;
      for (int i = 0; i < A->rows; i++) {
        if (i == row) continue;

        for (int j = 0; j < A->columns; j++) {
          if (j == column) continue;

          result->matrix[idx][jdx++] = A->matrix[i][j];
        }

        idx++;
        jdx = 0;
      }
    }
  }

  return res;
}

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

void free_2d_array(double **arr, int height) {
  if (arr != NULL) {
    for (int i = 0; i < height; i++)
      if (arr[i] != NULL) free(arr[i]);
    free(arr);
  }
}

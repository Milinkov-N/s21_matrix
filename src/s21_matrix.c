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

/*
 *
 * =============== UTILITY FUNCTIONS ===============
 *
 */

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

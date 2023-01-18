#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = ERR;

  if (result != NULL && rows > 0 && columns > 0) {
    res = OK;
  }

  return res;
}

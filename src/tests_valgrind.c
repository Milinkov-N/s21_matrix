#include "s21_matrix.h"

void tc_create_matrix() {
  {
    matrix_t mat = {0};
    s21_create_matrix(2, 2, &mat);
    s21_remove_matrix(&mat);
  }

  {
    matrix_t mat;
    s21_create_matrix(2, 2, &mat);
    s21_remove_matrix(&mat);
  }

  {
    matrix_t mat;
    s21_create_matrix(4, 4, &mat);
    s21_remove_matrix(&mat);
  }

  {
    matrix_t mat;
    s21_create_matrix(-4, -4, &mat);
    s21_remove_matrix(&mat);
  }
}

int main(void) {
  tc_create_matrix();
  return 0;
}

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

  { s21_create_matrix(-4, -4, NULL); }
}

void tc_eq_matrix() {
  {
    CREATE_MATRIX(mat1, 2, 2, {{1, 2}, {3, 4}});
    CREATE_MATRIX(mat2, 2, 2, {{1, 2}, {3, 4}});
    s21_eq_matrix(&mat1, &mat2);
    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 2, 2, {{1.1234567, 2.1234567}, {3.1234567, 4.1234567}});
    CREATE_MATRIX(mat2, 2, 2, {{1.1234567, 2.1234567}, {3.1234567, 4.1234567}});
    s21_eq_matrix(&mat1, &mat2);
    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 1, 2, {{1.1234567, 2.1234567}});
    CREATE_MATRIX(mat2, 2, 2, {{1.1234567, 2.1234567}, {3.1234567, 4.1234567}});
    s21_eq_matrix(&mat1, &mat2);
    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t mat1 = {0}, mat2 = {0};

    s21_create_matrix(3, 3, &mat1);
    s21_create_matrix(3, 3, &mat2);

    mat1.matrix[0][0] = 1.1234568;
    mat2.matrix[0][0] = 1.1234567;
    s21_eq_matrix(&mat1, &mat2);
    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t mat1 = {0}, mat2 = {0};
    s21_eq_matrix(&mat1, &mat2);
  }

  {
    matrix_t mat1, mat2;
    s21_eq_matrix(&mat1, &mat2);
  }
}

int main(void) {
  tc_create_matrix();
  tc_eq_matrix();
  return 0;
}

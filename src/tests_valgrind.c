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

void tc_sum_matrix() {
  {
    CREATE_MATRIX(mat1, 1, 1, {{14}});
    CREATE_MATRIX(mat2, 1, 1, {{23}});

    matrix_t res_mat = {0};

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 2, 2, {{14, 43}, {-5, 12.47}});
    CREATE_MATRIX(mat2, 2, 2, {{23, -12.51}, {50, 0}});

    matrix_t res_mat = {0};

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 3,
                  {{0, 13, -4}, {-5, 17.357, 400}, {321.5672, -0.001, 2.5}});
    CREATE_MATRIX(mat2, 3, 3,
                  {{15.5, -12.51, 99.98},
                   {521.125, 0.34, 0.019855},
                   {516.301, 10, -11.12}});

    matrix_t res_mat = {0};

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }

  {
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

    matrix_t res_mat = {0};

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 4, 4,
                  {{0, 13, -4, 1},
                   {-5, 17.357, 400, 88.80},
                   {321.5672, -0.001, 2.5, 75.75},
                   {0.005001, 1, 36.6, 420.18}});
    CREATE_MATRIX(mat2, 2, 4,
                  {{15.5, -12.51, 99.98, 0}, {521.125, 0.34, 0.019855, 7}});

    matrix_t res_mat = {0};

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
    CREATE_MATRIX(mat2, 2, 4,
                  {{15.5, -12.51, 99.98, 0}, {521.125, 0.34, 0.019855, 7}});

    matrix_t res_mat = {0};

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
    CREATE_MATRIX(mat2, 3, 4,
                  {{15.5, -12.51, 99.98, 0},
                   {521.125, 0.34, 0.019855, 7},
                   {521.125, 0.34, 0.019855, 7}});

    matrix_t res_mat = {0};

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t mat1 = {0}, mat2 = {0}, res_mat = {0};

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t mat1, mat2, res_mat;

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
    CREATE_MATRIX(mat2, 3, 4,
                  {{15.5, -12.51, 99.98, 0},
                   {521.125, 0.34, 0.019855, 7},
                   {521.125, 0.34, 0.019855, 7}});
    matrix_t res_mat;

    s21_sum_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }
}

void tc_sub_matrix() {
  {
    CREATE_MATRIX(mat1, 1, 1, {{14}});
    CREATE_MATRIX(mat2, 1, 1, {{23}});

    matrix_t res_mat = {0};

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 2, 2, {{14, 43}, {-5, 12.47}});
    CREATE_MATRIX(mat2, 2, 2, {{23, -12.51}, {50, 0}});

    matrix_t res_mat = {0};

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 3,
                  {{0, 13, -4}, {-5, 17.357, 400}, {321.5672, -0.001, 2.5}});
    CREATE_MATRIX(mat2, 3, 3,
                  {{15.5, -12.51, 99.98},
                   {521.125, 0.34, 0.019855},
                   {516.301, 10, -11.12}});

    matrix_t res_mat = {0};

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }

  {
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

    matrix_t res_mat = {0};

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 4, 4,
                  {{0, 13, -4, 1},
                   {-5, 17.357, 400, 88.80},
                   {321.5672, -0.001, 2.5, 75.75},
                   {0.005001, 1, 36.6, 420.18}});
    CREATE_MATRIX(mat2, 2, 4,
                  {{15.5, -12.51, 99.98, 0}, {521.125, 0.34, 0.019855, 7}});

    matrix_t res_mat = {0};

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
    CREATE_MATRIX(mat2, 2, 4,
                  {{15.5, -12.51, 99.98, 0}, {521.125, 0.34, 0.019855, 7}});

    matrix_t res_mat = {0};

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
    CREATE_MATRIX(mat2, 3, 4,
                  {{15.5, -12.51, 99.98, 0},
                   {521.125, 0.34, 0.019855, 7},
                   {521.125, 0.34, 0.019855, 7}});

    matrix_t res_mat = {0};

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t mat1 = {0}, mat2 = {0}, res_mat = {0};

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t mat1, mat2, res_mat;

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 2, 3, {{0, 13, -4}, {-5, 17.357, 400}});
    CREATE_MATRIX(mat2, 3, 4,
                  {{15.5, -12.51, 99.98, 0},
                   {521.125, 0.34, 0.019855, 7},
                   {521.125, 0.34, 0.019855, 7}});
    matrix_t res_mat;

    s21_sub_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&res_mat);
  }
}

int main(void) {
  tc_create_matrix();
  tc_eq_matrix();
  tc_sum_matrix();
  tc_sub_matrix();
  return 0;
}

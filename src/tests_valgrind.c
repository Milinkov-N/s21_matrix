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

  {
    CREATE_MATRIX(mat1, 3, 3,
                  {{0, 13, -4}, {-5, 17.357, 400}, {321.5672, -0.001, 2.5}});
    CREATE_MATRIX(mat2, 3, 3,
                  {{15.5, -12.51, 99.98},
                   {521.125, 0.34, 0.019855},
                   {516.301, 10, -11.12}});
    s21_sum_matrix(&mat1, &mat2, NULL);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t res_mat = {0};
    s21_sum_matrix(NULL, NULL, &res_mat);
  }

  { s21_sum_matrix(NULL, NULL, NULL); }
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

  {
    CREATE_MATRIX(mat1, 3, 3,
                  {{0, 13, -4}, {-5, 17.357, 400}, {321.5672, -0.001, 2.5}});
    CREATE_MATRIX(mat2, 3, 3,
                  {{15.5, -12.51, 99.98},
                   {521.125, 0.34, 0.019855},
                   {516.301, 10, -11.12}});
    s21_sub_matrix(&mat1, &mat2, NULL);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t res_mat = {0};
    s21_sub_matrix(NULL, NULL, &res_mat);
  }

  { s21_sub_matrix(NULL, NULL, NULL); }
}

void tc_mult_number() {
  {
    CREATE_MATRIX(mat1, 1, 1, {{14}});
    CREATE_MATRIX(exp_mat, 1, 1, {{70}});

    matrix_t res_mat = {0};

    s21_mult_number(&mat1, 5, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 2, 2, {{14, 5.05}, {70, 23.12}});
    CREATE_MATRIX(exp_mat, 2, 2, {{42.238, 15.23585}, {211.19, 69.75304}});

    matrix_t res_mat = {0};

    s21_mult_number(&mat1, 3.017, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 3,
                  {{14, 5.05, -10}, {70, 23.12, -22.23}, {0, 35.1, 7}});
    CREATE_MATRIX(exp_mat, 3, 3,
                  {{-14.14, -5.1005, 10.1},
                   {-70.7, -23.3512, 22.4523},
                   {0, -35.451, -7.07}});

    matrix_t res_mat = {0};

    s21_mult_number(&mat1, -1.01, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
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

    s21_mult_number(&mat1, 2.0032, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 1, 4, {{14, 5.05, -10, 101}});
    CREATE_MATRIX(exp_mat, 1, 4, {{28.0448, 10.11616, -20.032, 202.3232}});

    matrix_t res_mat = {0};

    s21_mult_number(&mat1, 2.0032, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 4, 1, {{14}, {5.05}, {-10}, {101}});
    CREATE_MATRIX(exp_mat, 4, 1,
                  {{28.0448}, {10.11616}, {-20.032}, {202.3232}});

    matrix_t res_mat = {0};

    s21_mult_number(&mat1, 2.0032, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    matrix_t mat1 = {0}, res_mat = {0};
    s21_mult_number(&mat1, 2.0032, &res_mat);
  }

  {
    matrix_t res_mat = {0};
    s21_mult_number(NULL, 2.0032, &res_mat);
  }

  {
    CREATE_MATRIX(mat1, 4, 1, {{14}, {5.05}, {-10}, {101}});
    s21_mult_number(&mat1, 2.0032, NULL);
    s21_remove_matrix(&mat1);
  }

  { s21_mult_number(NULL, 2.0032, NULL); }
}

void tc_mult_matrix() {
  {
    CREATE_MATRIX(mat1, 1, 1, {{14}});
    CREATE_MATRIX(mat2, 1, 1, {{4}});
    CREATE_MATRIX(exp_mat, 1, 1, {{56}});

    matrix_t res_mat = {0};

    s21_mult_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 2, 2, {{14, 12.456}, {-3, 0}});
    CREATE_MATRIX(mat2, 2, 2, {{4, -18}, {10, 5}});
    CREATE_MATRIX(exp_mat, 2, 2, {{180.56, -189.72}, {-12, 54}});

    matrix_t res_mat = {0};

    s21_mult_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 3, {{14, 12.456, -1}, {-3, 0, 13}, {4.04, -80, 6}});
    CREATE_MATRIX(mat2, 3, 3, {{4, -18, 7.07}, {10, 5, 6}, {20, 0, 420}});
    CREATE_MATRIX(exp_mat, 3, 3,
                  {{160.56, -189.72, -246.284},
                   {248, 54, 5438.79},
                   {-663.84, -472.72, 2068.5628}});

    matrix_t res_mat = {0};

    s21_mult_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 4, 4,
                  {{14, 12.456, -1, 5},
                   {-3, 0, 13, -10},
                   {4.04, -80, 6, 56},
                   {0.001, -2.5, 3.6, 0.7983}});
    CREATE_MATRIX(mat2, 4, 4,
                  {{4, -18, 7.07, 1},
                   {10, 5, 6, 2},
                   {20, 0, 420, 1},
                   {0, 30, 7.78, -12}});
    CREATE_MATRIX(exp_mat, 4, 4,
                  {{160.56, -39.72, -207.384, -22.088},
                   {248, -246, 5360.99, 130},
                   {-663.84, 1207.28, 2504.2428, -821.96},
                   {47.004, 11.431, 1503.217844, -10.9786}});

    matrix_t res_mat = {0};

    s21_mult_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 2, 4, {{14, 12.456, -1, 5}, {-3, 0, 13, -10}});
    CREATE_MATRIX(mat2, 4, 2, {{4, -18}, {10, 5}, {20, 0}, {0, 30}});
    CREATE_MATRIX(exp_mat, 2, 2, {{160.56, -39.72}, {248, -246}});

    matrix_t res_mat = {0};

    s21_mult_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 1, {{14}, {-3}, {4.04}});
    CREATE_MATRIX(mat2, 1, 3, {{4, -18, 7.07}});
    CREATE_MATRIX(
        exp_mat, 3, 3,
        {{56, -252, 98.98}, {-12, 54, -21.21}, {16.16, -72.72, 28.5628}});

    matrix_t res_mat = {0};

    s21_mult_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 1, {{14}, {-3}, {4.04}});
    CREATE_MATRIX(mat2, 1, 3, {{4, 0.0 / 0.0, 7.07}});

    matrix_t res_mat = {0};

    s21_mult_matrix(&mat1, &mat2, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    CREATE_MATRIX(mat1, 3, 1, {{14}, {-3}, {4.04}});
    CREATE_MATRIX(mat2, 1, 3, {{4, 0, 7.07}});

    s21_mult_matrix(&mat1, &mat2, NULL);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&mat2);
  }

  {
    matrix_t mat1 = {0}, mat2 = {0}, res_mat = {0};
    s21_mult_matrix(&mat1, &mat2, &res_mat);
  }

  {
    matrix_t res_mat = {0};
    s21_mult_matrix(NULL, NULL, &res_mat);
  }

  { s21_mult_matrix(NULL, NULL, NULL); }
}

void tc_transpose() {
  {
    CREATE_MATRIX(mat1, 1, 1, {{14}});
    CREATE_MATRIX(exp_mat, 1, 1, {{14}});

    matrix_t res_mat = {0};

    s21_transpose(&mat1, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 2, 2, {{14, 15}, {-1, 0}});
    CREATE_MATRIX(exp_mat, 2, 2, {{14, -1}, {15, 0}});

    matrix_t res_mat = {0};

    s21_transpose(&mat1, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 3, {{14, 15, -2}, {0, 50, 3}, {17, -0.001, 6}});
    CREATE_MATRIX(exp_mat, 3, 3, {{14, 0, 17}, {15, 50, -0.001}, {-2, 3, 6}});

    matrix_t res_mat = {0};

    s21_transpose(&mat1, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 2, 4, {{14, 15, -2, 90}, {0, 50, 3, 10}});
    CREATE_MATRIX(exp_mat, 4, 2, {{14, 0}, {15, 50}, {-2, 3}, {90, 10}});

    matrix_t res_mat = {0};

    s21_transpose(&mat1, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 1, {{14}, {3}, {0}});
    CREATE_MATRIX(exp_mat, 1, 3, {{14, 3, 0}});

    matrix_t res_mat = {0};

    s21_transpose(&mat1, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    matrix_t mat = {0}, res_mat = {0};
    s21_transpose(&mat, &res_mat);
  }

  {
    CREATE_MATRIX(mat1, 3, 1, {{14}, {3}, {0}});
    s21_transpose(&mat1, NULL);
    s21_remove_matrix(&mat1);
  }

  {
    matrix_t res_mat = {0};
    s21_transpose(NULL, &res_mat);
  }

  { s21_transpose(NULL, NULL); }
}

void tc_determinant() {
  {
    CREATE_MATRIX(mat, 1, 1, {{14}});
    double res_val = 0;
    s21_determinant(&mat, &res_val);
    s21_remove_matrix(&mat);
  }

  {
    CREATE_MATRIX(mat, 2, 2, {{4, 1}, {0, 9}});
    double res_val = 0;
    s21_determinant(&mat, &res_val);
    s21_remove_matrix(&mat);
  }

  {
    CREATE_MATRIX(mat, 3, 3, {{4, 1, 2.5}, {0, 9, 7.1}, {0.001, 0, 0}});
    double res_val = 0;
    s21_determinant(&mat, &res_val);
    s21_remove_matrix(&mat);
  }

  {
    CREATE_MATRIX(mat, 4, 4,
                  {{4, 1, 2.5, 3},
                   {0, 9, 7.1, -2},
                   {0.001, 0, 0, 5},
                   {0, 25.568, 30, -40.95}});
    double res_val = 0;
    s21_determinant(&mat, &res_val);
    s21_remove_matrix(&mat);
  }

  {
    CREATE_MATRIX(mat, 4, 4,
                  {{4, 1, 2.5, 3},
                   {0, 9, 7.1, -2},
                   {0.001, 0, 0, 5},
                   {0, 25.568, 30, -40.95}});
    s21_determinant(&mat, NULL);
    s21_remove_matrix(&mat);
  }

  {
    double res_val = 0;
    s21_determinant(NULL, &res_val);
  }

  { s21_determinant(NULL, NULL); }

  {
    matrix_t mat = {0};
    double res_val = 0;
    s21_determinant(&mat, &res_val);
  }
}

void tc_calc_complements() {
  {
    matrix_t res_mat = {0};
    CREATE_MATRIX(mat1, 3, 3, {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}});
    CREATE_MATRIX(exp_mat, 3, 3, {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}});

    s21_calc_complements(&mat1, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    matrix_t res_mat = {0};
    CREATE_MATRIX(mat1, 2, 2, {{1, 2}, {4, 6}});
    CREATE_MATRIX(exp_mat, 2, 2, {{6, -4}, {-2, 1}});

    s21_calc_complements(&mat1, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    matrix_t res_mat = {0};
    CREATE_MATRIX(mat1, 1, 1, {{1}});
    s21_calc_complements(&mat1, &res_mat);
    s21_remove_matrix(&mat1);
  }

  {
    matrix_t res_mat = {0};
    CREATE_MATRIX(
        mat1, 4, 4,
        {{1, 2, 0, 3}, {4, 6, -2, 17}, {-5, 0, 0, -4}, {0, 0, 12, -14}});
    CREATE_MATRIX(exp_mat, 4, 4,
                  {{288, 688, -420, -360},
                   {-96, -132, 140, 120},
                   {-136, 32, 28, 24},
                   {-16, -22, 72, 20}});

    s21_calc_complements(&mat1, &res_mat);

    s21_remove_matrix(&mat1);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    matrix_t mat1 = {0}, res_mat = {0};
    s21_calc_complements(&mat1, &res_mat);
  }

  { s21_calc_complements(NULL, NULL); }
}

void tc_inverse_matrix() {
  {
    CREATE_MATRIX(mat, 1, 1, {{5}});
    CREATE_MATRIX(exp_mat, 1, 1, {{0.2}});
    matrix_t res_mat = {0};

    s21_inverse_matrix(&mat, &res_mat);

    s21_remove_matrix(&mat);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat, 2, 2, {{5, 2}, {0, -3}});
    CREATE_MATRIX(exp_mat, 2, 2, {{-3, -2}, {0, 5}});
    matrix_t res_mat = {0};

    s21_inverse_matrix(&mat, &res_mat);

    s21_remove_matrix(&mat);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat, 3, 3, {{2, 5, 7}, {6, 3, 4}, {5, -2, -3}});
    CREATE_MATRIX(exp_mat, 3, 3, {{-1, 1, -1}, {38, -41, 34}, {-27, 29, -24}});
    matrix_t res_mat = {0};

    s21_inverse_matrix(&mat, &res_mat);

    s21_remove_matrix(&mat);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(mat, 4, 4,
                  {{2.14, -5, 0.7, 11},
                   {16, 3.01, 0, 7},
                   {5.55, -2.5, -3.33, 0},
                   {10, -10, 0, -1.0156}});
    CREATE_MATRIX(exp_mat, 4, 4,
                  {{-222.92033652, 384.98704, -46.8601308, 239.0563},
                   {-287.211168, 377.48297472, -60.37472, -509.0016},
                   {-155.9098942, 358.24944, -2379.08988584, 780.5605},
                   {633.033, 73.888, 133.07, -327.543712}});

    matrix_t res_mat = {0};

    s21_inverse_matrix(&mat, &res_mat);

    s21_remove_matrix(&mat);
    s21_remove_matrix(&exp_mat);
    s21_remove_matrix(&res_mat);
  }

  {
    CREATE_MATRIX(
        mat, 3, 4,
        {{2.14, -5, 0.7, 11}, {16, 3.01, 0, 7}, {5.55, -2.5, -3.33, 0}});
    matrix_t res_mat = {0};
    s21_inverse_matrix(&mat, &res_mat);
    s21_remove_matrix(&mat);
  }

  {
    CREATE_MATRIX(mat, 4, 4,
                  {{2.14, -5, 0.7, 11},
                   {16, 3.01, 0, 7},
                   {5.55, -2.5, -3.33, 0},
                   {10, -10, 0, -1.0156}});
    s21_inverse_matrix(&mat, NULL);
    s21_remove_matrix(&mat);
  }

  {
    matrix_t res_mat = {0};
    s21_inverse_matrix(NULL, &res_mat);
  }

  { s21_inverse_matrix(NULL, NULL); }

  {
    matrix_t mat = {0}, res_mat = {0};
    s21_inverse_matrix(&mat, &res_mat);
  }
}

int main(void) {
  tc_create_matrix();
  tc_eq_matrix();
  tc_sum_matrix();
  tc_sub_matrix();
  tc_mult_number();
  tc_mult_matrix();
  tc_transpose();
  tc_determinant();
  tc_calc_complements();
  tc_inverse_matrix();
  return 0;
}

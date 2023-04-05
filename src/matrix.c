#include "matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix *Matrix_create_empty(size_t width, size_t height) {
  Matrix *mat = malloc(sizeof(Matrix));
  // make sure the struct allocated
  if (!mat)
    return NULL;
  mat->width = width;
  mat->height = height;
  mat->_elems = malloc(width * height * sizeof(double));
  // Make sure the internal array was actually allocated!
  if (!mat->_elems) {
    free(mat);
    return NULL;
  }
  memset(mat->_elems, 0, sizeof(*mat->_elems));
  // The matrix is zeroed out.
  return mat;
}

Matrix *Matrix_create_filled(size_t width, size_t height,
                             double elems[width * height]) {
  if (width == 0 || height == 0)
    return NULL;

  Matrix *mat = malloc(sizeof(Matrix));
  if (!mat)
    return NULL;

  mat->width = width;
  mat->height = height;
  mat->_elems = elems;
  // the matrix was initialized with the given list of elements.
  return mat;
}

Matrix *Matrix_clone(Matrix *mat) {
  if (!mat)
    return NULL;

  Matrix *new = Matrix_create_empty(mat->width, mat->height);
  if (!new)
    return NULL;

  memcpy(new->_elems, mat->_elems, new->width *new->height * sizeof(double));
  return new;
}

void Matrix_free(Matrix *mat) {
  free(mat->_elems);
  free(mat);
}

double Matrix_get(Matrix *mat, size_t y, size_t x) {
  if (y < mat->height && x < mat->width)
    return mat->_elems[y * mat->width + x];
  return 0.0;
}

int Matrix_set(Matrix *mat, size_t y, size_t x, double val) {
  if (y >= mat->height || x >= mat->width) {
    return 1;
  }
  mat->_elems[y * mat->width + x] = val;
  return 0;
}

void Matrix_print(Matrix *mat) {
  if (!mat) {
    printf("NULL\n");
    return;
  }

  for (size_t y = 0; y < mat->height; y++) {
    printf("|");
    for (size_t x = 0; x < mat->width; x++) {
      printf("%f", Matrix_get(mat, y, x));
      if (x != mat->width - 1) {
        printf(" | ");
      }
    }
    printf("|\n");
  }
}

bool Matrix_check_eq_size(Matrix *mat1, Matrix *mat2) {
  return (mat1->width == mat2->width && mat1->height == mat2->height);
}

Matrix *Matrix_add(Matrix *mat1, Matrix *mat2) {
  // aw hell nah no nulls
  if (!mat1 || !mat2)
    return NULL;

  // make sure the matrices are equal sizeeeeee
  if (!Matrix_check_eq_size(mat1, mat2))
    return NULL;

  size_t w = mat1->width, h = mat1->height;
  Matrix *result = Matrix_create_empty(w, h);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < h; y++) {
    for (size_t x = 0; x < w; x++) {
      Matrix_set(result, y, x,
                 (Matrix_get(mat1, y, x) + Matrix_get(mat2, y, x)));
    }
  }
  return result;
}

Matrix *Matrix_sub(Matrix *mat1, Matrix *mat2) {
  // aw hell nah no nulls
  if (!mat1 || !mat2)
    return NULL;

  // make sure the matrices are equal sizeeeeee
  if (!Matrix_check_eq_size(mat1, mat2))
    return NULL;

  size_t w = mat1->width, h = mat1->height;
  Matrix *result = Matrix_create_empty(w, h);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < h; y++) {
    for (size_t x = 0; x < w; x++) {
      Matrix_set(result, y, x,
                 (Matrix_get(mat1, y, x) - Matrix_get(mat2, y, x)));
    }
  }
  return result;
}

Matrix *Matrix_scalar_mul(Matrix *mat, double scalar) {
  // aw hell nah no nulls
  if (!mat)
    return NULL;

  size_t w = mat->width, h = mat->height;
  Matrix *result = Matrix_create_empty(w, h);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < h; y++) {
    for (size_t x = 0; x < w; x++) {
      Matrix_set(result, y, x, (Matrix_get(mat, y, x) * scalar));
    }
  }
  return result;
}

Matrix *Matrix_mul(Matrix *mat1, Matrix *mat2) {
  if (!mat1 || !mat2)
    return NULL;

  if (mat1->width != mat2->height)
    return NULL;

  Matrix *result = Matrix_create_empty(mat2->width, mat1->height);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < result->height; y++) {
    for (size_t x = 0; x < result->width; x++) {
      double num = 0;
      for (size_t i = 0; i < mat1->width; i++) {

        // multiply the two numbers together
        num += Matrix_get(mat1, y, i) * Matrix_get(mat2, i, x);
      }
      Matrix_set(result, y, x, num);
    }
  }
  return result;
}

Matrix *Matrix_rot_right(Matrix *mat) {
  if (!mat)
    return NULL;

  // create an empty matrix with the rotated dimensions
  Matrix *result = Matrix_create_empty(mat->height, mat->width);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < mat->height; y++) {
    for (size_t x = 0; x < mat->width; x++) {
      Matrix_set(result, x, (result->width - 1) - y, Matrix_get(mat, y, x));
    }
  }
  return result;
}

Matrix *Matrix_rot_left(Matrix *mat) {
  if (!mat)
    return NULL;

  // create an empty matrix with the rotated dimensions
  Matrix *result = Matrix_create_empty(mat->height, mat->width);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < mat->height; y++) {
    for (size_t x = 0; x < mat->width; x++) {
      Matrix_set(result, (result->height - 1) - x, y, Matrix_get(mat, y, x));
    }
  }
  return result;
}

Matrix *Matrix_rot_180(Matrix *mat) {
  if (!mat)
    return NULL;

  // create an empty matrix with the right dimensions
  Matrix *result = Matrix_create_empty(mat->width, mat->height);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < mat->height; y++) {
    for (size_t x = 0; x < mat->width; x++) {
      Matrix_set(result, (result->width - 1) - y, (result->height - 1) - x,
                 Matrix_get(mat, y, x));
    }
  }
  return result;
}

Matrix *Matrix_flip_horiz(Matrix *mat) {
  if (!mat)
    return NULL;

  // create an empty matrix with the right dimensions
  Matrix *result = Matrix_create_empty(mat->width, mat->height);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < mat->height; y++) {
    for (size_t x = 0; x < mat->width; x++) {
      Matrix_set(result, y, (result->width - 1) - x, Matrix_get(mat, y, x));
    }
  }
  return result;
}

Matrix *Matrix_flip_vert(Matrix *mat) {
  if (!mat)
    return NULL;

  // create an empty matrix with the right dimensions
  Matrix *result = Matrix_create_empty(mat->width, mat->height);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < mat->height; y++) {
    for (size_t x = 0; x < mat->width; x++) {
      Matrix_set(result, (result->height - 1) - y, x, Matrix_get(mat, y, x));
    }
  }
  return result;
}

Matrix *Matrix_transpose(Matrix *mat) {
  if (!mat)
    return NULL;

  // create an empty matrix with the right dimensions
  Matrix *result = Matrix_create_empty(mat->height, mat->width);

  // make sure that allocation was successful
  if (!result)
    return NULL;

  for (size_t y = 0; y < mat->height; y++) {
    for (size_t x = 0; x < mat->width; x++) {
      Matrix_set(result, x, y, Matrix_get(mat, y, x));
    }
  }
  return result;
}

static double _Matrix_det_recursive(double mul, Matrix *mat, size_t size,
                                    size_t y_start, size_t x_start,
                                    bool original) {

  static size_t original_size;
  static bool *x_skip = NULL;
  if (original) {
    original_size = size;
  }
  if (!x_skip && original && size >= 4) {
    x_skip = calloc(size, sizeof(bool));
  }

  // These are some hard-coded cases that dramatically speed up performance of
  // this inefficient asf algorithm
  if (size == 0) {
    // what lol
    return 0;
  } else if (size == 1) {
    // get the only element
    return Matrix_get(mat, y_start, x_start);
  } else if (size == 2) {
    size_t second;
    for (size_t x = x_start + 1; x < original_size; x++) {
      if (!x_skip || x_skip[x] == false) {
        second = x;
        break;
      }
    }
    // determinant = a * d - b * c
    return (Matrix_get(mat, y_start, x_start) *
                Matrix_get(mat, y_start + 1, second) -
            Matrix_get(mat, y_start, second) *
                Matrix_get(mat, y_start + 1, x_start)) *
           mul;
  } else if (size == 3) {
    size_t second = x_start + 1;
    bool second_is_good = false;
    size_t third = x_start + 2;
    while (x_skip && x_skip[second] == true) {
      second++;
    }
    while (x_skip && (x_skip[third] == true || third == second)) {
      third++;
    }
    double num1 = Matrix_get(mat, y_start, x_start) *
                  (Matrix_get(mat, y_start + 1, second) *
                       Matrix_get(mat, y_start + 2, third) -
                   Matrix_get(mat, y_start + 1, third) *
                       Matrix_get(mat, y_start + 2, second));
    double num2 = Matrix_get(mat, y_start, second) *
                  (Matrix_get(mat, y_start + 1, x_start) *
                       Matrix_get(mat, y_start + 2, third) -
                   Matrix_get(mat, y_start + 1, third) *
                       Matrix_get(mat, y_start + 2, x_start));
    double num3 = Matrix_get(mat, y_start, third) *
                  (Matrix_get(mat, y_start + 1, x_start) *
                       Matrix_get(mat, y_start + 2, second) -
                   Matrix_get(mat, y_start + 1, second) *
                       Matrix_get(mat, y_start + 2, x_start));
    return mul * (num1 - num2 + num3);
  }

  bool add = true;
  double determinant = 0;
  size_t left = x_start + 1;

  // loop through all sub-matrices that we need to find determinants of
  size_t x_idx = x_start;
  for (size_t xout = 0; xout < size; x_idx++) {
    if (x_skip[x_idx] == true) {
      continue;
    }
    if (x_idx == original_size) {
      break;
    }
    x_skip[x_idx] = true;
    for (size_t st = x_start; st < original_size; st++) {
      if (x_skip[st] == false) {
        left = st;
        break;
      }
    }

    // add determinant of sub-matrix to total determinant of matrix
    if (add) {
      determinant += _Matrix_det_recursive(Matrix_get(mat, y_start, x_idx), mat,
                                           size - 1, y_start + 1, left, false);
    } else {
      determinant -= _Matrix_det_recursive(Matrix_get(mat, y_start, x_idx), mat,
                                           size - 1, y_start + 1, left, false);
    }
    // next operation is opposite
    add = !add;

    x_skip[x_idx] = false;
    xout++;
  }

  if (original) {
    free(x_skip);
    x_skip = NULL;
  }
  return mul * determinant;
}

int Matrix_determinant(Matrix *mat, double *result) {
  if (!mat)
    return 1;
  if (mat->width != mat->height)
    return 1;

  *result = _Matrix_det_recursive(1, mat, mat->width, 0, 0, true);
  return 0;
}

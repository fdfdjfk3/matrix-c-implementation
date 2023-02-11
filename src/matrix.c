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

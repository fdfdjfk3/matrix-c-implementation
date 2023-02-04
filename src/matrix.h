#include <stdbool.h>
#include <stdlib.h>

#ifndef MATRIX_H
#define MATRIX_H

/**
 * A two-dimensional immutably-sized Matrix of doubles.
 * Can manipulated in any function that starts with 'Matrix_'.
 */
typedef struct {
  /**
   * The width of the matrix
   */
  size_t width;
  /**
   * The height of the matrix
   */
  size_t height;
  /**
   * The internal elements of the Matrix. This should never be manually
   * modified. Use Matrix_get() and Matrix_set() instead.
   */
  double *_elems;
} Matrix;

/**
 * Creates an empty (zeroed) Matrix.
 *
 * @param width The width of the Matrix as size_t.
 * @param height The height of the Matrix as size_t.
 * @return A reference to the allocated Matrix
 */
Matrix *Matrix_create_empty(size_t width, size_t height);

/**
 * Creates a Matrix with an initialized array of elements.
 *
 * @param width The width of the Matrix as size_t.
 * @param height The height of the Matrix as size_t.
 * @param elems The list of elements in an array of doubles of size width *
 * height
 * @return A reference to the allocated Matrix
 */
Matrix *Matrix_create_filled(size_t width, size_t height,
                             double elems[width * height]);

/**
 * Clones a matrix
 *
 * @param mat The matrix to be cloned
 * @return A reference to the allocated Matrix
 */
Matrix *Matrix_clone(Matrix *mat);

/**
 * Frees the memory taken up by the matrix. Use this function over regular
 * free() because this function also frees the internal elements of the matrix.
 *
 * @param mat The matrix to be freed.
 */
void Matrix_free(Matrix *mat);

/**
 * Gets the value of a spot in the matrix.
 *
 * @param mat The matrix
 * @param y Y position in matrix
 * @param x X position in matrix
 * @return The value
 */
double Matrix_get(Matrix *mat, size_t y, size_t x);

/**
 * Sets the value of a spot in the matrix.
 *
 * @param mat The matrix
 * @param y Y position in matrix
 * @param x X position in matrix
 * @param val Value to be set
 * @return 0 if operation was successful and 1 if operation was not successful
 */
int Matrix_set(Matrix *mat, size_t y, size_t x, double val);

/**
 * Prints the contents of a matrix neatly. If the given Matrix pointer is NULL,
 * this function will simply print "NULL"
 *
 * @param mat A reference to the Matrix to be printed.
 */
void Matrix_print(Matrix *mat);

/**
 * Compares two matrices to see if they are equal in size
 *
 * @param mat1 Matrix 1
 * @param mat2 Matrix 2
 * @return true or false depending on if the sizes are equal.
 */
bool Matrix_check_eq_size(Matrix *mat1, Matrix *mat2);

/**
 * Adds two matrices together and creates a new Matrix with the result. The
 * matrices must be equal width and height.
 *
 * @param mat1 Matrix 1
 * @param mat2 Matrix 2
 * @return Pointer to new allocated Matrix, or NULL if something went wrong.
 */
Matrix *Matrix_add(Matrix *mat1, Matrix *mat2);

/**
 * Subtracts two matrices and creates a new Matrix with the result. The matrices
 * must be of equal width & height.
 *
 * @param mat1 Matrix 1
 * @param mat2 Matrix 2
 * @return Pointer to new allocated Matrix, or NULL if something went wrong.
 */
Matrix *Matrix_sub(Matrix *mat1, Matrix *mat2);

/**
 * Multiples a Matrix by a scalar value and creates a new Matrix with the
 * result.
 *
 * @param mat The Matrix
 * @param scalar The scalar (multiplier) of the matrix
 * @return Pointer to new allocated Matrix, or NULL if something went wrong.
 */
Matrix *Matrix_scalar_mul(Matrix *mat, double scalar);

/**
 * Multiplies two matrices together and creates a new Matrix with the result.
 * Matrix 1's width must equal Matrix 2's height.
 *
 * @param mat1 Matrix 1
 * @param mat2 Matrix 2
 * @return Pointer to new allocated Matrix, or NULL if something went wrong.
 */
Matrix *Matrix_mul(Matrix *mat1, Matrix *mat2);

/**
 * Rotates a Matrix 90 degrees to the right.
 *
 * @param mat The Matrix
 * @return Pointer to new allocated Matrix, or NULL if something went wrong.
 */
Matrix *Matrix_rot_right(Matrix *mat);

/**
 * Rotates a Matrix 90 degrees to the left.
 *
 * @param mat The Matrix
 * @return Pointer to new allocated Matrix, or NULL if something went wrong.
 */
Matrix *Matrix_rot_left(Matrix *mat);

/**
 * Rotates a Matrix by 180 degrees. This is equivalent to using
 * Matrix_rot_left() or Matrix_rot_right() twice.
 *
 * @param mat The Matrix
 * @return Pointer to new allocated Matrix, or NULL if something went wrong.
 */
Matrix *Matrix_rot_180(Matrix *mat);

#endif

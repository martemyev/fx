#ifndef DENSE_MATRIX_HPP
#define DENSE_MATRIX_HPP

#include <iostream>

namespace FX {

class DenseMatrix
{
public:

  /**
   * Constructor allocates the memory for the matrix according to its size and
   * initializes the elements with a default value
   * @param n_rows - number of rows of the matrix
   * @param n_cols - number of columns of the matrix
   * @param value - default value of the elements
   */
  explicit DenseMatrix(int n_rows,
                       int n_cols,
                       double value = 0.);

  /**
   * Constructor allocates the memory for the matrix according to its size and
   * initializes the elements with a given array. Typical usage:
   @verbatim
   double array[] = { 1, 2, 3, 4 };
   DenseMatrix mat(2, 2, array);
   @endverbatim
   * @note There is no way to check if the array provided through the
   * pointer has the declared number of elements. Therefore, be careful - it is
   * in developer's responsibility.
   * @param n_rows - number of rows of the matrix
   * @param n_cols - number of columns of the matrix
   * @param array - 1D array of values initializing the matrix. Depending on the
   * number of rows and columns and the order of arranging the elements in the
   * matrix the values of the array will be put in the internal _data 1D array.
   */
  explicit DenseMatrix(int n_rows,
                       int n_cols,
                       double *array);

  /**
   * Copy constructor
   * @param mat - a matrix from which the copy is made
   */
  DenseMatrix(const DenseMatrix &mat);

  /**
   * Constructor loads the matrix from a given stream
   */
  explicit DenseMatrix(std::istream &in);

  /**
   * Copy assignment operator
   * @param mat - a matrix from which the copy is made
   * @return newly created (deeply copied) matrix
   */
  DenseMatrix& operator =(const DenseMatrix &mat);

  /**
   * Destructor frees the memory allocated for the matrix (calls clean())
   */
  ~DenseMatrix();

  /**
   * Clean the memory allocated for the matrix
   */
  void clean();

  int n_rows() const { return _n_rows; }
  int n_cols() const { return _n_cols; }
  bool square() const { return _n_rows == _n_cols; }

  /**
   * Get the data (linear array representing the matrix), so that the array may
   * be changed. This is used in LAPACK functions, for example.
   */
  double* data() { return _data; }
  const double* data() const { return _data; }


  /**
   * Get an element of the matrix
   * @param i - row of the element
   * @param j - column of the element
   * @return a copy of the element (the element itself is safe)
   */
  double operator ()(int i, int j) const;

  /**
   * Get an element of the matrix
   * @param i - row of the element
   * @param j - column of the element
   * @return a reference to the element (the element can be changed)
   */
  double& operator ()(int i, int j);


protected: // =========================== PROTECTED ============================

  int _n_rows; ///< The number of rows of the matrix
  int _n_cols; ///< The number of columns of the matrix

  /// The values of the dense matrix (which is a 2D array) are kept in linear
  /// (1D) array of contiguous memory
  double *_data;

};

} // namespace FX


#endif // DENSE_MATRIX_HPP

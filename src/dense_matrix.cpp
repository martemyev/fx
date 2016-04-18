#include "dense_matrix.hpp"

#include <stdexcept>

namespace FX {


DenseMatrix::DenseMatrix(int nrows, int ncols, double value)
  : _n_rows(nrows)
  , _n_cols(ncols)
  , _data(nullptr)
{
  _data = new double[_n_rows * _n_cols];
  for (int i = 0; i < _n_rows*_n_cols; ++i)
    _data[i] = value;
}




DenseMatrix::DenseMatrix(int nrows, int ncols, double *array)
  : _n_rows(nrows)
  , _n_cols(ncols)
  , _data(nullptr)
{
  if (!array) {
    throw std::runtime_error("The array provided to initialize the dense "
                             "matrix is NULL");
  }

  _data = new double[_n_rows * _n_cols];
  for (int i = 0; i < _n_rows*_n_cols; ++i)
    _data[i] = array[i];
}




DenseMatrix::DenseMatrix(const DenseMatrix &mat)
  : _n_rows(mat._n_rows)
  , _n_cols(mat._n_cols)
  , _data(nullptr)
{
  _data = new double[_n_rows * _n_cols];
  for (int i = 0; i < _n_rows*_n_cols; ++i)
    _data[i] = mat._data[i];
}




DenseMatrix::DenseMatrix(std::istream &in)
  : _n_rows(0)
  , _n_cols(0) // dummy parameters (will be overwritten anyway)
  , _data(nullptr)
{
  if (!in.good()) {
    throw std::runtime_error("Input stream is in bad state");
  }

  std::string line;
  in >> _n_rows >> _n_cols;
  getline(in, line); // read what's left in the line

  _data = new double[_n_rows * _n_cols];
  for (int i = 0; i < _n_rows; ++i) {
    for (int j = 0; j < _n_cols; ++j) {
      in >> (*this)(i, j);
    }
    getline(in, line);
  }
}




DenseMatrix& DenseMatrix::operator =(const DenseMatrix &mat)
{
  // because it possible that 'this' matrix has been already created, we need to
  // clean it first (nothing happens if the matrix hasn't been allocated)
  clean();

  _n_rows = mat._n_rows;
  _n_cols = mat._n_cols;

  _data = new double[_n_rows * _n_cols];
  for (int i = 0; i < _n_rows*_n_cols; ++i)
    _data[i] = mat._data[i];

  return *this;
}




DenseMatrix::~DenseMatrix()
{
  clean();
}




void DenseMatrix::clean()
{
  _n_rows = 0;
  _n_cols = 0;
  delete[] _data;
}




double DenseMatrix::operator ()(int i, int j) const
{
//  expect(_data, "The memory for this matrix is not allocated");
//  expect(i >= 0 && i < _n_rows, "Row number (" + d2s(i) + ") is out of range "
//         "[0, " + d2s(_n_rows) + ")");
//  expect(j >= 0 && j < _n_cols, "Column number (" + d2s(j) + ") is out of "
//         "range [0, " + d2s(_n_cols) + ")");

  return _data[i*_n_cols + j];
}




double& DenseMatrix::operator ()(int i, int j)
{
//  expect(_data, "The memory for this matrix is not allocated");
//  expect(i >= 0 && i < _n_rows, "Row number is out of range");
//  expect(j >= 0 && j < _n_cols, "Column number (" + d2s(j) + ") is out of range"
//         " [0, " + d2s(_n_cols) + ")");

  return _data[i*_n_cols + j];
}



} // namespace FX

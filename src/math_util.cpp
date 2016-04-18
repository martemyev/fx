#include "math_util.hpp"

#include <stdexcept>

namespace FX {
namespace MathUtil {

int nextPow2(int x) {
  if (x < 1)
    throw std::runtime_error("x must be greater or equal 1");
  if ((x & (x - 1)) == 0) {
    return x; // x is already a power-of-two number
  }

  x |= (x >> 1);
  x |= (x >> 2);
  x |= (x >> 4);
  x |= (x >> 8);
  x |= (x >> 16);
  return x + 1;
}

DenseMatrix padSamples(const DenseMatrix &source, int length) {
  if (length <= source.n_cols())
    throw std::runtime_error("There is no room for padding");

  DenseMatrix result(source.n_rows(), length);
  for (int i = 0; i < source.n_rows(); ++i) {
    int j = 0;
    for (; j < source.n_cols(); ++j) {
      result(i, j) = source(i, j);
    }
    for (; j < length; ++j) {
      result(i, j) = 0.;
    }
  }
}

} // namespace MathUtil
} // namespace FX

#ifndef MATH_UTIL_HPP
#define MATH_UTIL_HPP

#include "dense_matrix.hpp"

namespace FX {
namespace MathUtil {

int nextPow2(int x);

DenseMatrix padSamples(const DenseMatrix &source, int length);


} // namespace MathUtil
} // namespace FX


#endif // MATH_UTIL_HPP

#include "complex.hpp"

#include <iostream>

int main() {
  fx::Complex c(4.0, 5.0);

  std::cout << c << std::endl;
  std::cout << fx::Complex::ZERO << std::endl;

  return 0;
}


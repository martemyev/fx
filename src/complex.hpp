#include <cmath>
#include <iostream>
#include <vector>

namespace FX {

class Complex {

public:
    
  static const Complex ZERO;
  static const Complex ONE;
  static const Complex I;

  explicit Complex() : x(0.0), y(0.0) {}
  explicit Complex(double x_, double y_) : x(x_), y(y_) {}
  Complex(const Complex &c) : x(c.x), y(c.y) {}
  Complex& operator =(const Complex &c) {
    x = c.x;
    y = c.y;
    return *this;
  }
  ~Complex() {}

  Complex plus(const Complex &c) const {
    return Complex(x + c.x, y + c.y);
  }

  Complex minus(const Complex &c) const {
    return Complex(x - c.x, y - c.y);
  }
    
  Complex times(const Complex &c) const {
    return Complex(x * c.x - y * c.y, x * c.y + y * c.x);
  }
    
  Complex times(double d) const {
    return Complex(x * d, y * d);
  }

  Complex dividedBy(const Complex &c) const {
    return this->times(c.conjugate()).times(1.0 / c.norm());
  }

  Complex dividedBy(double d) const {
    return Complex(x / d, y / d);
  }

  Complex conjugate() const {
    return Complex(x, -y);
  }

  Complex inverse() const {
    return Complex::ONE.dividedBy(*this);
  }

  double norm() const {
    return x * x + y * y;
  }

  friend std::ostream& operator << (std::ostream &out, const Complex &c) {
    if (c.y == 0.0) {
      out << c.x;
    } else if (c.x == 0.0) {
      out << c.y << "*i";
    } else if (c.y > 0.0) {
      out << c.x << "+i*" << c.y;
    } else {
      out << c.x << "-i*" << (-c.y);
    }
    return out;
  }

  double real() const {
    return x;
  }

  double imag() const {
    return y;
  }

  double abs() const {
    return std::sqrt(this->norm());
  }

  Complex pow(int n) const {
    if (n == 0)
      return Complex(1, 0);
    if (n < 0)
      return Complex(1, 0).dividedBy(this->pow(-n));
    if (n == 1)
      return *this;
    Complex z2 = this->pow(n / 2);
    z2 = z2.times(z2);
    if (n % 2 == 0)
      return z2;
    return z2.times(*this);
  }

  void sqrts(Complex *values) const {
    Complex principalRoot = sqrt();
    values[0] = principalRoot;
    values[1] = principalRoot.times(-1);
  }

  Complex sqrt() const {
    return Complex::fromPolar(std::sqrt(this->abs()), this->arg() / 2);
  }

  Complex nthRoot(int n) const {
    return Complex::fromPolar(std::pow(this->abs(), 1.0 / n), this->arg() / n);
  }

  std::vector<Complex> nthRoots(int n) {
    Complex principalRoot = nthRoot(n);
    std::vector<Complex> rtn(n);
    std::vector<bool> flags(n, false);
    rtn[0] = principalRoot;
    const Complex rootOfUnity = Complex::fromPolar(1, M_PI * 2 / n);
    const Complex otherRoot = rootOfUnity.conjugate();
    for (int i = 1, j = n - 1; i < n; i++, j--) {
      if (flags[i])
        break;
      rtn[i] = rtn[i - 1].times(rootOfUnity);
      flags[i] = true;
      if (flags[j])
        break;
      rtn[j] = rtn[(j + 1) % n].times(otherRoot);
      flags[j] = true;
    }
    return rtn;
  }

  static Complex fromPolar(double r, double theta) {
    return Complex(r * std::cos(theta), r * std::sin(theta));
  }

  double arg() const {
    return atan2(y, x);
  }

  Complex exp() const {
    return Complex::fromPolar(std::exp(x), y);
  }

  Complex cosh() const {
    const Complex e = exp();
    return e.plus(e.inverse()).dividedBy(2);
  }

  Complex sinh() const {
    const Complex e = exp();
    return e.minus(e.inverse()).dividedBy(2);
  }

  Complex tanh() const {
    return sinh().dividedBy(cosh());
  }

  Complex sech() const {
    return cosh().inverse();
  }

  Complex cosech() const {
    return sinh().inverse();
  }

  Complex coth() const {
    return cosh().dividedBy(sinh());
  }

  Complex cos() const {
    return this->times(Complex::I).cosh();
  }

  Complex sin() const {
    return this->times(Complex::I).sinh().dividedBy(Complex::I);
  }

  Complex tan() const {
    return sin().dividedBy(cos());
  }

  Complex cot() const {
    return cos().dividedBy(sin());
  }

  Complex cosec() const {
    return Complex::ONE.dividedBy(sin());
  }

  Complex sec() const {
    return Complex::ONE.dividedBy(cos());
  }
    
  /**
   * Warning! Logs of complex numbers are not uniquely defined. This returns a
   * particular branch of the log function. There are infinitely many branches,
   * to get others, add multiples of Complex.I.times(2*M_PI) to the answer
   * returned here.
   */
  Complex log() const {
    return log(0);
  }

  Complex log(double suggestedArg) const {
    double arg = this->arg();
    while (arg < suggestedArg - M_PI)
      arg += M_PI * 2;
    while (arg > suggestedArg + M_PI)
      arg -= M_PI * 2;
    return Complex(std::log(this->abs()), arg);
  }

private:
  double x, y;

};

} // namespace FX

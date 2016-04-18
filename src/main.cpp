#include "complex.hpp"
#include "dense_matrix.hpp"
#include "math_util.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace FX;

int main() {

  try {

    std::string fname = "/home/artemyev/known_traces.txt";
    std::ifstream in(fname.c_str());
    if (!in) {
      throw std::runtime_error("Can't open file " + fname);
    }

    std::string line; // line of a text from an input file

    int multiple;
    getline(in, line);
    std::istringstream(line) >> multiple;

    int nTraces;
    getline(in, line);
    std::istringstream(line) >> nTraces;

    int nSamples;
    double **knownTraces = new double*[nTraces];
    for (int tr = 0; tr < nTraces; ++tr) {
      in >> nSamples;
      if (nSamples == 0) {
        knownTraces[tr] = nullptr;
      } else {
        knownTraces[tr] = new double[nSamples];
        for (int s = 0; s < nSamples; ++s)
          in >> knownTraces[tr][s];
      }
      getline(in, line); // the rest of the line
    }

    std::cout << multiple << " " << nTraces << std::endl;

  } catch (...) {
    std::cout << "\n\n\tUnknown exception!\n\n" << std::flush;
  }

  return 0;
}


#include "Matrix.hpp"
#include <iostream>
#include <vector>

template <class type>
Matrix<type>::Matrix(int rows, int columns, std::vector<type> elems)
    : num_rows(rows), num_columns(columns), elements(elems) {}

template <class type> void Matrix<type>::print_matrix() {
  for (int i = 0; i < elements.size(); i++) {
    std::cout << elements.at(i) << " ";
    if ((i + 1) % num_columns == 0)
      std::cout << std::endl;
  }
}

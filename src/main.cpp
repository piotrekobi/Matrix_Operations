#include "Matrix.cpp"
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  Matrix<int> A(2, 2, {1, 2, 3, 4});
  Matrix<float> B(2, 2, {3, 3, 4, 5});

  A.print_matrix();
  std::cout << std::endl;
  B.print_matrix();
  return 0;
}

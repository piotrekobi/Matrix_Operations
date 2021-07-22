#include <vector>

template <class type> class Matrix {
  int num_rows, num_columns;
  std::vector<type> elements;

public:
  Matrix(int rows, int columns, std::vector<type> elems);
  void print_matrix();
};
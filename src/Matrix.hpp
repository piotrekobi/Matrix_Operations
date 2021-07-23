#include <vector>

template <class type> class Matrix
{
    unsigned int num_rows, num_columns;
    std::vector<type> elements;

  public:
    Matrix(int rows, int columns, std::vector<type> elems);
    Matrix<type> operator*(const Matrix &);
    bool operator==(const Matrix &);
    void print_matrix();
};
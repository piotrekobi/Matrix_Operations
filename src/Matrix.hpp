#include <vector>

template <class type> class Matrix
{
    unsigned int num_rows, num_columns;
    std::vector<type> elements;
    static bool floating_point_compare(const type &, const type &);
    static void check_multiplication_possibility(const Matrix<type> &A, const Matrix<type> &B);
    static std::vector<Matrix<type>> compute_partial_derivatives(Matrix<type> &A, Matrix<type> &B, Matrix<type> &C);
    static std::vector<type> compute_gradient_elements(Matrix<type> &A, Matrix<type> &B, Matrix<type> &C,
                                                       std::vector<Matrix<type>> partial_derivatives);
    static void fill_elements_C_equal_A(std::vector<type> &gradient_elements,
                                        std::vector<Matrix<type>> partial_derivatives, Matrix<type> &B);
    static void fill_elements_C_equal_B(std::vector<type> &gradient_elements,
                                        std::vector<Matrix<type>> partial_derivatives, Matrix<type> &B, const int i);

  public:
    Matrix(int rows, int columns, std::vector<type> elems);
    Matrix<type> operator*(const Matrix &);
    static Matrix<type> compute_grad(Matrix<type> &A, Matrix<type> &B, Matrix<type> &C);

    bool operator==(const Matrix &);
    void print_matrix();
};
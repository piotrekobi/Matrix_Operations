#include <vector>

template <class type> class Matrix
{
    unsigned const int num_rows, num_columns;
    std::vector<type> const elements;
    static bool floating_point_compare(const type &, const type &);
    static void check_multiplication_possibility(const Matrix<type> &A, const Matrix<type> &B);
    static std::vector<Matrix<type>> compute_partial_derivatives(Matrix<type> &A, Matrix<type> &B,
                                                                 const bool right_derivative);
    static std::vector<type> compute_gradient_elements(const std::vector<Matrix<type>> partial_derivatives,
                                                       const int num_columns, const int num_rows,
                                                       const bool right_derivative);
    static void fill_elements_C_equal_A(std::vector<type> &gradient_elements, const std::vector<type> &row_sums,
                                        const int num_columns);
    static void fill_elements_C_equal_B(std::vector<type> &gradient_elements,
                                        std::vector<Matrix<type>> partial_derivatives, const int num_columns,
                                        const int current_row);
    static void fill_row_sums(std::vector<type> &row_sums, std::vector<Matrix<type>> partial_derivatives);

  public:
    Matrix(const int rows, const int columns, const std::vector<type> elems);
    Matrix<type> operator*(const Matrix &);
    static Matrix<type> compute_grad(Matrix<type> &A, Matrix<type> &B, Matrix<type> &C);

    bool operator==(const Matrix &);
    void print_matrix();
};
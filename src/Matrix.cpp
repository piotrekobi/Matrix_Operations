#include "Matrix.hpp"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

template <class type>
Matrix<type>::Matrix(const int rows, const int columns, const std::vector<type> elems)
    : num_rows(rows), num_columns(columns), elements(elems)
{
    if (elems.size() != rows * columns)
    {
        throw std::invalid_argument("Invalid number of elements for a " + std::to_string(rows) + std::string("x") +
                                    std::to_string(columns) + std::string(" matrix"));
    }
}

template <class type> void Matrix<type>::check_multiplication_possibility(const Matrix<type> &A, const Matrix<type> &B)
{
    if (A.num_columns != B.num_rows)
    {
        throw std::invalid_argument("The number of columns of the first matrix is "
                                    "not equal to the number of "
                                    "rows of the second matrix");
    }
}

template <class type> Matrix<type> Matrix<type>::operator*(const Matrix<type> &A)
{
    check_multiplication_possibility(*this, A);
    std::vector<type> result_elems;
    for (int result_matrix_index = 0; result_matrix_index < this->num_rows * A.num_columns; result_matrix_index++)
    {
        type value = 0;
        for (int column_index = 0; column_index < this->num_columns; column_index++)
        {
            int matrix_1_element_index = this->num_columns * (result_matrix_index / A.num_columns) + column_index;
            int matrix_2_elememt_index = A.num_columns * column_index + (result_matrix_index % A.num_columns);
            value += (this->elements.at(matrix_1_element_index) * (A.elements.at(matrix_2_elememt_index)));
        }
        result_elems.push_back(value);
    }
    return Matrix<type>(this->num_rows, A.num_columns, result_elems);
}

template <class type>
std::vector<Matrix<type>> Matrix<type>::compute_partial_derivatives(Matrix<type> &A, Matrix<type> &B,
                                                                    const bool right_derivative)
{
    int num_partial_derivatives = A.num_columns;
    std::vector<Matrix<type>> partial_derivatives;

    for (int i = 0; i < num_partial_derivatives; i++)
    {
        std::vector<type> elements(num_partial_derivatives, 0);
        elements.at(i) = 1;
        if (right_derivative)
        {
            partial_derivatives.push_back(A * Matrix<type>(A.num_columns, 1, elements));
        }
        else
        {
            partial_derivatives.push_back(Matrix<type>(1, B.num_rows, elements) * B);
        }
    }
    return partial_derivatives;
}

template <class type>
void Matrix<type>::fill_row_sums(std::vector<type> &row_sums, std::vector<Matrix<type>> partial_derivatives)
{
    for (int num_column = 0; num_column < partial_derivatives.at(0).elements.size(); num_column++)
    {
        type row_sum = 0;
        for (int num_row = 0; num_row < partial_derivatives.size(); num_row++)
            row_sum += partial_derivatives.at(num_row).elements.at(num_column);
        row_sums.push_back(row_sum);
    }
}

template <class type>
void Matrix<type>::fill_elements_C_equal_A(std::vector<type> &gradient_elements, const std::vector<type> &row_sums,
                                           const int num_columns)
{
    for (int num_column = 0; num_column < num_columns; num_column++)
        gradient_elements.push_back(row_sums.at(num_column));
}

template <class type>
void Matrix<type>::fill_elements_C_equal_B(std::vector<type> &gradient_elements,
                                           std::vector<Matrix<type>> partial_derivatives, const int num_columns,
                                           const int current_row)
{
    type column_sum = 0;
    for (int num_partial_derivative = 0; num_partial_derivative < partial_derivatives.size(); num_partial_derivative++)
        column_sum += partial_derivatives.at(num_partial_derivative).elements.at(current_row);
    for (int num_column = 0; num_column < num_columns; num_column++)
        gradient_elements.push_back(column_sum);
}

template <class type>
std::vector<type> Matrix<type>::compute_gradient_elements(const std::vector<Matrix<type>> partial_derivatives,
                                                          const int num_columns, const int num_rows,
                                                          const bool right_derivative)
{
    std::vector<type> gradient_elements;
    std::vector<type> row_sums;
    if (!right_derivative)
        fill_row_sums(row_sums, partial_derivatives);

    for (int current_row = 0; current_row < num_rows; current_row++)
    {
        if (right_derivative)
            fill_elements_C_equal_B(gradient_elements, partial_derivatives, num_columns, current_row);
        else
            fill_elements_C_equal_A(gradient_elements, row_sums, num_columns);
    }
    return gradient_elements;
}

template <class type> Matrix<type> Matrix<type>::compute_grad(Matrix<type> &A, Matrix<type> &B, Matrix<type> &C)
{
    if (!(C == A) and !(C == B))
        throw std::invalid_argument("The gradient matrix must be either the first or the second multiplied matrix");

    check_multiplication_possibility(A, B);
    bool right_derivative = (C == B);
    std::vector<Matrix<type>> partial_derivatives = compute_partial_derivatives(A, B, right_derivative);
    std::vector<type> gradient_elements =
        compute_gradient_elements(partial_derivatives, B.num_columns, A.num_rows, right_derivative);

    return Matrix<type>(A.num_rows, B.num_columns, gradient_elements);
}

template <class type> bool Matrix<type>::floating_point_compare(const type &x, const type &y)
{
    return abs(x - y) < 0.00001;
}

template <class type> bool Matrix<type>::operator==(const Matrix<type> &A)
{
    return ((this->num_columns == A.num_columns) && (this->num_rows == A.num_rows) &&
            (std::equal(this->elements.begin(), this->elements.end(), A.elements.begin(), floating_point_compare)));
}

template <class type> void Matrix<type>::print_matrix()
{
    for (int current_element = 0; current_element < elements.size(); current_element++)
    {
        std::cout << std::setw(4) << elements.at(current_element) << " ";
        if ((current_element + 1) % num_columns == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

template class Matrix<float>;
template class Matrix<double>;

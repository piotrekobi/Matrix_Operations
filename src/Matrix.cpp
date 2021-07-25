#include "Matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

template <class type>
Matrix<type>::Matrix(int rows, int columns, std::vector<type> elems)
    : num_rows(rows), num_columns(columns), elements(elems)
{
    if (elems.size() != rows * columns)
    {
        throw std::invalid_argument("Invalid number of elements for a " + std::to_string(rows) + std::string("x") +
                                    std::to_string(columns) + std::string(" matrix"));
    }
}

template <class type> Matrix<type> Matrix<type>::operator*(const Matrix<type> &A)
{
    if (this->num_columns != A.num_rows)
    {
        throw std::invalid_argument("The number of columns of the first matrix is "
                                    "not equal to the number of "
                                    "rows of the second matrix");
    }

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

template <class type> Matrix<type> Matrix<type>::compute_grad(Matrix<type> &A, Matrix<type> &B, Matrix<type> &C)
{
    std::vector<Matrix<type>> partial_derivatives;

    for (int i = 0; i < A.num_columns; i++)
    {
        std::vector<type> elements(A.num_columns, 0);
        elements.at(i) = 1;
        partial_derivatives.push_back(A * Matrix<type>(A.num_columns, 1, elements));
    }

    for (int i = 0; i < partial_derivatives.size(); i++)
    {
        partial_derivatives.at(i).print_matrix();
        std::cout << std::endl;
    }

    return partial_derivatives.at(0); // placeholder
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
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        std::cout << elements.at(i) << " ";
        if ((i + 1) % num_columns == 0)
            std::cout << std::endl;
    }
}

template class Matrix<float>;
template class Matrix<double>;

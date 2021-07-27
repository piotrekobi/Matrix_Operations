#include "Matrix.hpp"
#include <iostream>
#include <vector>

int main()
{
    Matrix<float> A(4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    Matrix<float> B(4, 4, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

    (A * B).print_matrix();
    Matrix<float>::compute_grad(A, B, B).print_matrix();
    Matrix<float>::compute_grad(A, B, A).print_matrix();

    return 0;
}

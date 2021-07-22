#include "Matrix.cpp"
#include <iostream>
#include <vector>

int main(int argc, char const *argv[])
{
    Matrix<float> A(1, 3, {1, 2.6, 3});
    Matrix<float> B(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    // Matrix<float> A(4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    // Matrix<float> B(4, 4, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

    // A.print_matrix();
    // std::cout << std::endl;
    // B.print_matrix();
    Matrix<float> C = A * B;
    C.print_matrix();
    return 0;
}

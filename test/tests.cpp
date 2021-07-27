#define CATCH_CONFIG_MAIN
#include <Matrix.hpp>
#include <catch2/catch.hpp>

TEST_CASE("Invalid matrix creation", "[matrix]")
{
    REQUIRE_THROWS_WITH(Matrix<float>(2, 2, {1}), "Invalid number of elements for a 2x2 matrix");
}

TEST_CASE("Invalid multiplication", "[matrix]")
{
    Matrix<float> Left(1, 3, {2, 4, 6});
    Matrix<float> Right(2, 2, {1, 2, 3, 4});
    REQUIRE_THROWS_WITH(
        Left * Right,
        "The number of columns of the first matrix is not equal to the number of rows of the second matrix");
}

TEST_CASE("Invalid derivative gradient matrix", "[matrix]")
{
    Matrix<double> A(1, 1, {2});
    Matrix<double> B(1, 3, {3, 5, 7});
    Matrix<double> InvalidGradient(2, 2, {1, 2, 3, 4});
    REQUIRE_THROWS_WITH(Matrix<double>::compute_grad(A, B, InvalidGradient),
                        "The gradient matrix must be either the first or the second multiplied matrix");
}

TEST_CASE("Invalid derivative multiplication matrices", "[matrix]")
{
    Matrix<double> A(1, 3, {2, 4, 6});
    Matrix<double> B(2, 2, {1, 2, 3, 4});
    REQUIRE_THROWS_WITH(
        Matrix<double>::compute_grad(A, B, A),
        "The number of columns of the first matrix is not equal to the number of rows of the second matrix");
}

TEST_CASE("1x1 and 1x1 multiplication", "[matrix]")
{
    Matrix<float> Left(1, 1, {2});
    Matrix<float> Right(1, 1, {3});
    Matrix<float> Result(1, 1, {6});
    REQUIRE((Left * Right == Result));

    Matrix<float> LeftGradient(1, 1, {3});
    Matrix<float> RightGradient(1, 1, {2});
    REQUIRE((Matrix<float>::compute_grad(Left, Right, Left) == LeftGradient));
    REQUIRE((Matrix<float>::compute_grad(Left, Right, Right) == RightGradient));
}

TEST_CASE("1x1 and 1x3 multiplication", "[matrix]")
{
    Matrix<double> Left(1, 1, {2});
    Matrix<double> Right(1, 3, {3, 5, 7});
    Matrix<double> Result(1, 3, {6, 10, 14});
    REQUIRE((Left * Right == Result));

    Matrix<double> LeftGradient(1, 3, {3, 5, 7});
    Matrix<double> RightGradient(1, 3, {2, 2, 2});
    REQUIRE((Matrix<double>::compute_grad(Left, Right, Left) == LeftGradient));
    REQUIRE((Matrix<double>::compute_grad(Left, Right, Right) == RightGradient));
}

TEST_CASE("2x3 and 3x5 multiplication", "[matrix]")
{
    Matrix<float> Left(2, 3, {2, 4, 6, 0, 1, 2});
    Matrix<float> Right(3, 5, {3, 5, 7, 9, 2, 4, 6, 8, 1, 2, 3, 4, 5, 6, 7});
    Matrix<float> Result(2, 5, {40, 58, 76, 58, 54, 10, 14, 18, 13, 16});
    REQUIRE((Left * Right == Result));

    Matrix<float> LeftGradient(2, 5, {10, 15, 20, 16, 11, 10, 15, 20, 16, 11});
    Matrix<float> RightGradient(2, 5, {12, 12, 12, 12, 12, 3, 3, 3, 3, 3});
    REQUIRE((Matrix<float>::compute_grad(Left, Right, Left) == LeftGradient));
    REQUIRE((Matrix<float>::compute_grad(Left, Right, Right) == RightGradient));
}

TEST_CASE("3x1 and 1x3 multiplication", "[matrix]")
{
    Matrix<double> Left(3, 1, {2, 4, 6});
    Matrix<double> Right(1, 3, {3, 5, 7});
    Matrix<double> Result(3, 3, {6, 10, 14, 12, 20, 28, 18, 30, 42});
    REQUIRE((Left * Right == Result));

    Matrix<double> LeftGradient(3, 3, {3, 5, 7, 3, 5, 7, 3, 5, 7});
    Matrix<double> RightGradient(3, 3, {2, 2, 2, 4, 4, 4, 6, 6, 6});
    REQUIRE((Matrix<double>::compute_grad(Left, Right, Left) == LeftGradient));
    REQUIRE((Matrix<double>::compute_grad(Left, Right, Right) == RightGradient));
}

TEST_CASE("4x4 and 4x4 multiplication", "[matrix]")
{
    Matrix<float> Left(4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16});
    Matrix<float> Right(4, 4, {17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});
    Matrix<float> Result(4, 4, {250, 260, 270, 280, 618, 644, 670, 696, 986, 1028, 1070, 1112, 1354, 1412, 1470, 1528});
    REQUIRE((Left * Right == Result));

    Matrix<float> LeftGradient(4, 4, {92, 96, 100, 104, 92, 96, 100, 104, 92, 96, 100, 104, 92, 96, 100, 104});
    Matrix<float> RightGradient(4, 4, {10, 10, 10, 10, 26, 26, 26, 26, 42, 42, 42, 42, 58, 58, 58, 58});
    REQUIRE((Matrix<float>::compute_grad(Left, Right, Left) == LeftGradient));
    REQUIRE((Matrix<float>::compute_grad(Left, Right, Right) == RightGradient));
}

TEST_CASE("2x2 and 2x2 floating point multiplication", "[matrix]")
{
    Matrix<double> Left(2, 2, {0.3, 1.2, 1.23, 0.77});
    Matrix<double> Right(2, 2, {1.12, 2.4, 0.23, 5});
    Matrix<double> Result(2, 2, {0.612, 6.72, 1.5547, 6.802});
    REQUIRE((Left * Right == Result));

    Matrix<double> LeftGradient(2, 2, {1.35, 7.4, 1.35, 7.4});
    Matrix<double> RightGradient(2, 2, {1.5, 1.5, 2, 2});
    REQUIRE((Matrix<double>::compute_grad(Left, Right, Left) == LeftGradient));
    REQUIRE((Matrix<double>::compute_grad(Left, Right, Right) == RightGradient));
}

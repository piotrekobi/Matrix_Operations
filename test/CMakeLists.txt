Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

add_executable(MatrixTests tests.cpp)
target_link_libraries(MatrixTests Matrix Catch2::Catch2)

add_test(NAME MatrixTests COMMAND MatrixTests)


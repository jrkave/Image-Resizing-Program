// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"

using namespace std;

// Test 1: Matrix_fill
// Fills 3x5 Matrix with value
// Checks if Matrix_at returns that value for each element
TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }

  delete mat; // delete the Matrix
}

// Test 2: Matrix_init
// Creates a 5x4 Matrix and tests correct initialization
TEST(test_init_basic) {
  Matrix *mat = new Matrix;
  const int width = 5;
  const int height = 4;
  Matrix_init(mat, width, height);

  delete mat;
}

// Test 3: Matrix_print
// Fills a 3x4 Matrix with 1's
// Checks if Matrix_print() prints properly to ostringstream
TEST(test_print_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 4);
  Matrix_fill(mat, 1);
  
  string expected = "3 4\n1 1 1 \n1 1 1 \n1 1 1 \n1 1 1 \n";
  ostringstream oss;
  Matrix_print(mat, oss);
  ASSERT_EQUAL(oss.str(), expected);

  delete mat;
}

// Test 4: Matrix_width
// Creates 3x4 Matrix and tests if correct width is returned
TEST(test_width_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 4);
  ASSERT_EQUAL(Matrix_width(mat), 3);
  delete mat;
}

// Test 5: Matrix_height()
// Creates 3x4 Matrix and tests if correct height is returned
TEST(test_height_basic) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 3, 4);
  ASSERT_EQUAL(Matrix_height(mat), 4);
  delete mat;
}

// Test 6: Matrix_fill_border
// Creates a 5x4 Matrix, fills with 2's, fills border with 0's
// Verifies correct Matrix with Matrix_print function
TEST(test_matrix_at) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 5, 4); // width = row, height = column
  Matrix_fill(mat, 2);
  Matrix_fill_border(mat, 0);
  string expected = "5 4\n0 0 0 0 0 \n0 2 2 2 0 \n0 2 2 2 0 \n0 0 0 0 0 \n";
  ostringstream oss;
  Matrix_print(mat, oss);
  ASSERT_EQUAL(oss.str(), expected);
  delete mat;
}

// Test 6: Matrix_row() - returns row of element pointed to by ptr
// Creates 3x4 Matrix and checks if correct row is returned
TEST(test_return_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 4);
  Matrix_fill(mat, 2);
  Matrix_fill_border(mat, 0);
  const int *ptr = Matrix_at(mat, 3, 3);
  ASSERT_EQUAL(Matrix_row(mat, ptr), 3);
  delete mat;
}

// Test 7: Matrix_column() - returns column of element pointed to by ptr
TEST(test_return_column) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 4);
  Matrix_fill(mat, 2);
  Matrix_fill_border(mat, 0);
  const int *ptr = Matrix_at(mat, 3, 1);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 1);
  ptr = Matrix_at(mat, 3, 0);
  ASSERT_EQUAL(Matrix_column(mat, ptr), 0);
  delete mat;
}

// Testing Matrix_max finds largest number
// 1 2 3 4
// 5 6 7 8
// 9 10 11 12
// 13 14 15 16
TEST(test_max_val) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 4);
  Matrix_fill(mat, 1);
  int tempVal = 0;
  for (int i = 0; i < mat->height; i++) {
    for (int j = 0; j < mat->width; j++) {
      *Matrix_at(mat, i, j) = j + tempVal + 1;
    }
    tempVal += 4;
  }
  ASSERT_EQUAL(Matrix_max(mat), 16);
  *Matrix_at(mat, 2, 3) = 73;
  ASSERT_EQUAL(Matrix_max(mat), 73); // test new max
  delete mat;
}

// Testing Matrix_column_of_min_val_in_row() -- if tie, return LHS
TEST(test_col_min_val_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 4);
  Matrix_fill(mat, 1);
  int tempVal = 0;
  for (int i = 0; i < mat->height; i++) {
    for (int j = 0; j < mat->width; j++) {
      *Matrix_at(mat, i, j) = j + tempVal + 1;
    }
    tempVal += 4;
  }
  *Matrix_at(mat, 0, 0) = 0;
  *Matrix_at(mat, 0, 1) = 0;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 3), 0); // testing LHS
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 3), 0);
  *Matrix_at(mat, 1, 3) = 0;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 4), 3);
  delete mat;
}

// Testing Matrix_min_val_in_row()
TEST(min_val_in_row) {
  Matrix *mat = new Matrix;
  Matrix_init(mat, 4, 4);
  Matrix_fill(mat, 5);
  *Matrix_at(mat, 2, 2) = 0;
  *Matrix_at(mat, 3, 3) = 0;
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 2, 0, 3), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat, 3, 0, 4), 0); // edge
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

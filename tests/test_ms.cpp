#include "hdf5.hpp"
#include "model_selection.h"
#include "gtest/gtest.h"

class msTest : public ::testing::Test {
protected:
  virtual void SetUp() {
    // Load Data
    HDF5::File hf = HDF5::File("../data/iris.h5", HDF5::File::ReadOnly);
    hf.read("X", X);
    hf.read("y", y);
  }

  Eigen::MatrixXd X;
  Eigen::VectorXd y;
};

TEST_F(msTest, ttsShuffle) {
  auto [X_train, X_test, y_train, y_test] =
      test_train_split(X, y, 0.3333, true);
  int return_x_rows = X_train.rows() + X_test.rows();
  int return_y_rows = y_train.rows() + y_test.rows();

  EXPECT_EQ(X.rows(), return_x_rows);
  EXPECT_EQ(y.rows(), return_y_rows);
  EXPECT_NE(y_test(0), y(0));
  EXPECT_NE(X_test(0, 0), X.array()(0, 0));
}

TEST_F(msTest, ttsNoShuffle) {
  auto [X_train, X_test, y_train, y_test] =
      test_train_split(X, y, 0.3333, false);
  int return_x_rows = X_train.rows() + X_test.rows();
  int return_y_rows = y_train.rows() + y_test.rows();

  EXPECT_EQ(X.rows(), return_x_rows);
  EXPECT_EQ(y.rows(), return_y_rows);
  EXPECT_EQ(y_test(0), y(0));
  for (int i = 0; i < X.cols(); i++)
    EXPECT_EQ(X_test(0, i), X.array()(0, i));
}
#include "gtest/gtest.h"
#include "KNeighborsClassifier.h"
#include "hdf5.hpp"

TEST(TestKNN, Fitting){
    // Load Data
	HDF5::File hf = HDF5::File("../data/digits.h5", HDF5::File::ReadOnly);
    Eigen::MatrixXd X;
    Eigen::VectorXd y;
    Eigen::VectorXd y_predict;
    hf.read("X", X);
    hf.read("y", y);

    KNeighborsClassifier knn(5);
    knn.fit(X, y);
    ASSERT_TRUE(knn.is_fitted());
}
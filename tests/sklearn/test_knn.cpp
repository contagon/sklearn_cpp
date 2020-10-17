#include "gtest/gtest.h"
#include "hdf5.hpp"
#include "sklearn/KNeighborsClassifier.h"

class knnTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            // Load Data
            HDF5::File hf = HDF5::File("../data/iris.h5", HDF5::File::ReadOnly);
            hf.read("X", X);
            hf.read("y", y);
        }

        KNeighborsClassifier knn = KNeighborsClassifier(10, "uniform");
        Eigen::MatrixXd X;
        Eigen::VectorXd y;
};

TEST_F(knnTest, Fitting){
    knn.fit(X, y);
    EXPECT_TRUE(knn.is_fitted());
    EXPECT_EQ(knn.n_features(), X.cols());
}

// TEST(knnTest, NArgmax){
//     ArrayXd test = ArrayXi::LinSpaced(10,0,9);
//     ArrayXi idx = n_argmax(test, 1);

//     EXPECT_EQ(0, idx(0));
// }
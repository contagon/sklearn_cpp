#include "gtest/gtest.h"
#include "hdf5.hpp"
#include "Pipeline.h"

#include "StandardScaler.h"
#include "PCA.h"
#include "KNeighborsClassifier.h"

class pipeTest : public ::testing::Test {
    protected:
        virtual void SetUp() {
            // Load Data
            HDF5::File hf = HDF5::File("../data/iris.h5", HDF5::File::ReadOnly);
            hf.read("X", X);
            hf.read("y", y);
        }

        Eigen::MatrixXd X;
        Eigen::VectorXd y;
        Pipeline pipe = Pipeline( {{"std", new StandardScaler},
                                {"pca", new PCA(2)}, 
                                {"knn", new KNeighborsClassifier(10)}} );
};

TEST_F(pipeTest, Methods){
    // Check fitting
    pipe.fit(X, y);
    EXPECT_TRUE(pipe.is_fitted());
    EXPECT_EQ(pipe.n_features(), X.cols());

    // Check predicting
    ArrayXd y_predict = pipe.predict(X);
    EXPECT_EQ(y_predict.size(), y.size());

    // Check scoring
    EXPECT_NO_THROW( pipe.score(X, y) );
}

TEST_F(pipeTest, CopyProperties){
    Pipeline copy = pipe;

    // Make sure everything copied correctly
    EXPECT_EQ(copy.steps.size(), 3);
    EXPECT_EQ(copy.is_fitted(), pipe.is_fitted());

    // Make sure they're not connected inexplicitly
    copy.fit(X,y);
    EXPECT_NE(copy.is_fitted(), pipe.is_fitted());
}

TEST_F(pipeTest, Indexing){
    // Check indexing by numbers and by name
    BaseEstimator* pca1 = pipe["pca"];
    EXPECT_NO_THROW(dynamic_cast<PCA&>(*pca1));
    BaseEstimator* pca2 = pipe[1];
    EXPECT_NO_THROW(dynamic_cast<PCA&>(*pca2));

    // Check copying subpipe
    EXPECT_ANY_THROW(pipe(-1,2));
    EXPECT_ANY_THROW(pipe(0,5));
    EXPECT_NO_THROW( Pipeline subpipe = pipe(1,3); );
    Pipeline subpipe = pipe(1,3);
    EXPECT_EQ(subpipe.steps.size(), 2);
    // EXPECT_STREQ(subpipe.steps[0].first, "pca"s);
    // EXPECT_STREQ(subpipe.steps[1].first, "knn"s);
}

TEST_F(pipeTest, SetParams){
    // We'll set params for each method
    pipe.set_params({{"std__with_std", false},
                    {"pca__n_components", 3},
                    {"knn__n_neighbors", 30}});
    map<string, prm> params = pipe.get_params();
    EXPECT_FALSE(get<bool>(params["std__with_std"]));
    EXPECT_EQ(get<int>(params["pca__n_components"]), 3);
    EXPECT_EQ(get<int>(params["knn__n_neighbors"]), 30);
}
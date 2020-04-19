#ifndef MODEL_SELECTION
#define MODEL_SELECTION

#include <cmath>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

auto test_train_split(const ArrayXXd& X, const ArrayXd& y, float test_size, bool shuffle=true){
    // get number of items in test set
    int test_num = floor( test_size * X.rows() );

    // make indices and shuffle them
    ArrayXd idx = ArrayXd::LinSpaced(y.size(),0,y.size()-1);
    random_shuffle(idx.data(), idx.data()+y.size());

    // Split indices
    ArrayXd test_idx = idx( seq(0, test_num) );
    ArrayXd train_idx = idx( seq(test_num+1, last) );

    // Put into struct and return
    struct result {ArrayXXd X_train; ArrayXXd X_test; ArrayXd y_train; ArrayXd y_test;};
    return result{X(train_idx, all), X(test_idx, all), y(train_idx), y(test_idx)};
}

#endif
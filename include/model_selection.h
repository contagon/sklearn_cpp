#ifndef MODEL_SELECTION
#define MODEL_SELECTION

#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace std;

struct Split {
  ArrayXXd X_train;
  ArrayXXd X_test;
  ArrayXd y_train;
  ArrayXd y_test;
};
Split test_train_split(const ArrayXXd &X, const ArrayXd &y, float test_size,
                       bool shuffle = true);

#endif
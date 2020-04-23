#ifndef REGRESSOR
#define REGRESSOR

#include <Eigen/Dense>
#include "base.h"

using namespace Eigen;

class Regressor: public RegressorMixin{
    public:
        Regressor();
        ~Regressor() {}

        void fit(const ArrayXXd& X, const ArrayXd& y);
        ArrayXd predict(const ArrayXXd& X);
};

#endif
#ifndef STANDARDSCALER
#define STANDARDSCALER

#include <Eigen/Dense>
#include "base.h"

using namespace Eigen;

class StandardScaler: public TransformerMixin{
    public:
        bool with_mean;
        bool with_std;

        ArrayXd mean_;
        ArrayXd var_;
        ArrayXd scale_;

        StandardScaler(bool with_mean=true, bool with_std=true);
        ~StandardScaler() {}

        void fit(ArrayXXd X);
        void transform_inplace(ArrayXXd& X);
};

#endif
#ifndef TRANSFORMER
#define TRANSFORMER

#include <Eigen/Dense>
#include "base.h"

using namespace Eigen;

class MinMaxScaler: public TransformerMixin{
    public:
        float feature_min;
        float feature_max;
        ArrayXd scale_;
        ArrayXd min_;
        ArrayXd data_min_;
        ArrayXd data_max_;

        MinMaxScaler(float feature_min=0, float feature_max=1);
        ~MinMaxScaler() {}

        void fit(ArrayXXd X);
        void transform_inplace(ArrayXXd& X);
        void inverse_transform_inplace(ArrayXXd& X);
};

#endif
#ifndef TRANSFORMER
#define TRANSFORMER

#include <Eigen/Dense>
#include "base.h"

using namespace Eigen;

class Transfomer: public TransformerMixin{
    public:
        Transfomer();
        ~Transfomer() {}

        void fit(ArrayXXd X);
        void transform_inplace(ArrayXXd& X);
};

#endif
#ifndef TRANSFORMER
#define TRANSFORMER

#include <Eigen/Dense>
#include "base.h"

using namespace Eigen;

class Template: public TransformerMixin{
    public:
        Template();
        ~Template() {}

        void fit(ArrayXXd X);
        void transform_inplace(ArrayXXd& X);
};

#endif
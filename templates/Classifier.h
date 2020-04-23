#ifndef CLASSIFIER
#define CLASSIFIER

#include <Eigen/Dense>
#include "base.h"

using namespace Eigen;

class Classifier: public ClassifierMixin{
    public:
        Classifier();
        ~Classifier() {}

        void fit(const ArrayXXd& X, const ArrayXd& y);
        ArrayXd predict(const ArrayXXd& X);
};

#endif
#ifndef CLASSIFIER
#define CLASSIFIER

#include <Eigen/Dense>
#include <vector>
#include "base.h"

using namespace Eigen;

class Pipeline: public EstimatorMixin, public TransformerMixin{
    public:
        vector<BaseEstimator*> estimators;

        Pipeline(vector<BaseEstimator*> estimators);
        ~Pipeline();

        // Methods if we end with an Estimator
        void fit(const ArrayXXd& X, const ArrayXd& y);
        ArrayXd predict(const ArrayXXd& X);
        float score(const ArrayXXd& X, const ArrayXd& y);

        // Methods if they're all transformers
        void fit(ArrayXXd X);
        void transform_inplace(ArrayXXd& X);
        void inverse_transform_inplace(ArrayXXd& X);

        ArrayXXd transform(ArrayXXd X){
            transform_inplace(X);
            return X;
        }
        ArrayXXd inverse_transform(ArrayXXd X){
            inverse_transform_inplace(X);
            return X;
        }
        ArrayXXd fit_transform(ArrayXXd X){
            fit(X);
            return transform(X);
        }
        void fit_transform_inplace(ArrayXXd& X){
            fit(X);
            transform_inplace(X);
        }
};

#endif
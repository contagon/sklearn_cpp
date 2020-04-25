#ifndef CLASSIFIER
#define CLASSIFIER

#include <Eigen/Dense>
#include <vector>
#include "base.h"

using namespace Eigen;

class Pipeline: public EstimatorMixin, public TransformerMixin{
    public:
        vector<pair<string, BaseEstimator*>> estimators;

        Pipeline(vector<pair<string, BaseEstimator*>> estimators);
        ~Pipeline();

        // Methods if we end with an Estimator
        void fit(const ArrayXXd& X, const ArrayXd& y);
        ArrayXd predict(const ArrayXXd& X);
        float score(const ArrayXXd& X, const ArrayXd& y);

        // Methods if they're all transformers
        void fit(ArrayXXd X);
        void transform_inplace(ArrayXXd& X);
        void inverse_transform_inplace(ArrayXXd& X);

        // For indexing
        BaseEstimator& operator[](string goal_name);
};

#endif
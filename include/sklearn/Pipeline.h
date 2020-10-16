#ifndef CLASSIFIER
#define CLASSIFIER

#include <Eigen/Dense>
#include <vector>
#include "base.h"

using namespace std;
using namespace Eigen;

class Pipeline: public EstimatorMixin, public TransformerMixin{
    public:
        vector<pair<string, BaseEstimator*>> steps;

        Pipeline(vector<pair<string, BaseEstimator*>> steps);
        ~Pipeline();
        // copy and assignment operators
        Pipeline(const Pipeline& other);
        Pipeline& operator=(const Pipeline& rhs);

        // Methods if we end with an Estimator
        void fit(const ArrayXXd& X, const ArrayXd& y);
        ArrayXd predict(const ArrayXXd& X);
        float score(const ArrayXXd& X, const ArrayXd& y);

        // Methods if they're all transformers
        void fit(ArrayXXd X);
        void transform_inplace(ArrayXXd& X);
        void inverse_transform_inplace(ArrayXXd& X);

        // For indexing
        BaseEstimator* operator[](string goal_name);
        BaseEstimator* operator[](int idx);
        Pipeline operator()(int start, int stop);

        // Override set_params and get_params
        void set_params(map<string,prm> new_params);
        map<string, prm> get_params();

        virtual Pipeline* clone() const{
            return new Pipeline(*this);
        }
};

#endif
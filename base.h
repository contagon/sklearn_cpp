#ifndef BASE_INTERFACES
#define BASE_INTERFACES

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class BaseEstimator{
    protected:
        int features_ = 0;
        bool fitted_ = false;

        void check_X_y(const ArrayXXd& X, const ArrayXd& y){
            if(X.rows() != y.rows())
                throw std::invalid_argument( "X and y don't have same number of data points" );
            features_ = X.cols();
        }
        void check_X(const ArrayXXd& X){
            if(X.cols() != features_)
                throw std::invalid_argument( "Number of features of X has changed" );
        }
        void check_is_fitted(){
            if(!fitted_)
                throw std::invalid_argument( "Number of features of X has changed" );
        }
    public:
        BaseEstimator(void) {}
        ~BaseEstimator(void){}

        virtual void fit(const ArrayXXd& X, const ArrayXd& y) = 0;
        virtual ArrayXd predict(const ArrayXXd& X) = 0;
};

class RegressorMixin : public BaseEstimator{
    public:
        // For regressors return MSE as the metric
        float score(const ArrayXXd& X, const ArrayXd& y){

            ArrayXd prediction = predict(X);
            return (y-prediction).square().sum();
        }
};

class ClassifierMixin : public BaseEstimator{
    public:
        // For classifiers return accuracy as the metric
        float score(const ArrayXXd& X, const ArrayXd& y){

            ArrayXd prediction = predict(X);
            return (float)(y==prediction).count()/ (float)y.size();
        }
};

class TransformerMixin{
    public:
        virtual void fit(const ArrayXXd& X) = 0;
        virtual ArrayXXd& transform(const ArrayXXd& X) = 0;

        ArrayXXd fit_transform(const ArrayXXd& X){
            fit(X);
            return transform(X);
        }
};

#endif
#ifndef BASE_INTERFACES
#define BASE_INTERFACES

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class BaseEstimator{
    private: 
        bool fitted_ = false;
    protected:
        // For supervised methods 
        void check_X_y(const ArrayXXd& X, const ArrayXd& y){
            if(X.rows() != y.rows())
                throw std::invalid_argument( "X and y don't have same number of data points" );
            n_features_ = X.cols();
            fitted_ = true;
        }
        // For unsupervised methods
        void check_X_y(const ArrayXXd& X){
            n_features_ = X.cols();
            fitted_ = true;
        }
        void check_X(const ArrayXXd& X){
            if(X.cols() != n_features_)
                throw std::invalid_argument( "Number of features of X has changed" );
        }
        void check_is_fitted(){
            if(!fitted_)
                throw std::invalid_argument( "Estimator hasn't been fitted yet" );
        }
    public:
        int n_features_;
        BaseEstimator(void) {}
        ~BaseEstimator(void){}
};

class RegressorMixin : public BaseEstimator{
    public:
        virtual void fit(const ArrayXXd& X, const ArrayXd& y) = 0;
        virtual ArrayXd predict(const ArrayXXd& X) = 0;

        // For regressors return MSE as the metric
        float score(const ArrayXXd& X, const ArrayXd& y){

            ArrayXd prediction = predict(X);
            return (y-prediction).square().sum();
        }
};

class ClassifierMixin : public BaseEstimator{
    public:
        virtual void fit(const ArrayXXd& X, const ArrayXd& y) = 0;
        virtual ArrayXd predict(const ArrayXXd& X) = 0;

        // For classifiers return accuracy as the metric
        float score(const ArrayXXd& X, const ArrayXd& y){

            ArrayXd prediction = predict(X);
            return (float)(y==prediction).count() / (float)y.size();
        }
};

class TransformerMixin : public BaseEstimator{
    public:
        virtual void fit(ArrayXXd X) = 0;
        virtual void transform_inplace(ArrayXXd& X) = 0;

        // This will return a copy from the transform_inplace function
        ArrayXXd transform(ArrayXXd X){
            transform_inplace(X);
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
#ifndef BASE_INTERFACES
#define BASE_INTERFACES

#include <Eigen/Dense>
#include <map>
#include <variant>

using namespace Eigen;
using namespace std;

typedef variant<bool, int, float, string> prm;

class BaseEstimator{
    private: 
        bool fitted_ = false;
        int n_features_;
    protected:
        map<string, prm> params;
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
        // Return params 
        map<string, prm> get_params(){ return params; }
        // Set params using a map
        virtual void set_params(map<string,prm> new_params){
            for( auto [name, new_param] : new_params){
                if(params.count(name) == 1)
                    params[name] = new_param;
                else
                    throw invalid_argument("Invalid Parameter name");
            } 
        }
        bool is_fitted(){ return fitted_; }
        int  n_features(){ return n_features_; }
        
        BaseEstimator(void) {}
        BaseEstimator(map<string,prm> params) : params(params) {}
        virtual ~BaseEstimator(void){}
        // Clone 
        virtual BaseEstimator* clone() const = 0;
};

class EstimatorMixin : public virtual BaseEstimator{
    public:
        virtual void fit(const ArrayXXd& X, const ArrayXd& y) = 0;
        virtual ArrayXd predict(const ArrayXXd& X) = 0;
        virtual float score(const ArrayXXd& X, const ArrayXd& y) = 0;
};

class RegressorMixin : public EstimatorMixin{
    public:
        // For regressors return MSE as the metric
        float score(const ArrayXXd& X, const ArrayXd& y){
            // Make sure everything is in line
            check_is_fitted();
            check_X(X);
            return (y-predict(X)).square().sum();
        }
};

class ClassifierMixin : public EstimatorMixin{
    public:
        // For classifiers return accuracy as the metric
        float score(const ArrayXXd& X, const ArrayXd& y){
            // Make sure everything is in line
            check_is_fitted();
            check_X(X);
            return (float)(y==predict(X)).count() / (float)y.size();
        }
};

class TransformerMixin : public virtual BaseEstimator{
    public:
        virtual void fit(ArrayXXd X) = 0;
        virtual void transform_inplace(ArrayXXd& X) = 0;
        virtual void inverse_transform_inplace(ArrayXXd& X) = 0;

        // This will return a copy from the transform_inplace function
        ArrayXXd transform(ArrayXXd X){
            transform_inplace(X);
            return X;
        }
        ArrayXXd inverse_transform(ArrayXXd X){
            inverse_transform_inplace(X);
            return X;
        }

        // For faster transforming
        ArrayXXd fit_transform(ArrayXXd X){
            fit(X);
            return transform(X);
        }
        void fit_transform_inplace(ArrayXXd& X){
            fit(X);
            transform_inplace(X);
        }
        void fit(const ArrayXXd& X, const ArrayXd& y){
            fit(X);
        }
};

#endif
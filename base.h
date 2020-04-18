#ifndef BASE_INTERFACES
#define BASE_INTERFACES

#include <Eigen/Dense>

class BaseEstimator{
    public:
        BaseEstimator(void) {}
        ~BaseEstimator(void){}

        virtual void fit(const Eigen::ArrayXXd& X, const Eigen::ArrayXd& y) = 0;
        virtual Eigen::ArrayXd& predict(const Eigen::ArrayXXd& X) = 0;
};

class RegressorMixin : public BaseEstimator{
    public:
        // For regressors return MSE as the metric
        float score(const Eigen::ArrayXXd& X, const Eigen::ArrayXd& y){

            Eigen::ArrayXd& prediction = predict(X);
            return (y-prediction).square().sum();
        }
};

class ClassifierMixin : public BaseEstimator{
    public:
        // For classifiers return accuracy as the metric
        float score(const Eigen::ArrayXXd& X, const Eigen::ArrayXd& y){

            Eigen::ArrayXd& prediction = predict(X);
            return (float)(y==prediction).count()/ (float)y.size();
        }
};

class TransformerMixin{
    public:
        virtual void fit(const Eigen::ArrayXXd& X) = 0;
        virtual Eigen::ArrayXXd& transform(const Eigen::ArrayXXd& X) = 0;

        Eigen::ArrayXXd fit_transform(const Eigen::ArrayXXd& X){
            fit(X);
            return transform(X);
        }
};

#endif
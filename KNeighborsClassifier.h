#ifndef KNN_CLASSIFIER
#define KNN_CLASSIFIER

#include <Eigen/Dense>
#include "base.h"
#include <map>


class KNeighborsClassifier: public ClassifierMixin{
    public:
        int n_neighbors;
        string weights;
        Eigen::ArrayXXd X_;
        Eigen::ArrayXd y_;
    
        KNeighborsClassifier(int n_neighbors=5, string weights="uniform");
        ~KNeighborsClassifier() {}

        void fit(const Eigen::ArrayXXd& X, const Eigen::ArrayXd& y);
        Eigen::ArrayXd predict(const Eigen::ArrayXXd& X);
};

#endif
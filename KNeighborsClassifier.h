#ifndef KNN_CLASSIFIER
#define KNN_CLASSIFIER

#include <Eigen/Dense>
#include "base.h"

class KNeighborsClassifier: public ClassifierMixin{
    public:
        int n_neighbors;
        Eigen::ArrayXXd X;
        Eigen::ArrayXd y;
    
        KNeighborsClassifier(int n_neighbors=5);
        ~KNeighborsClassifier() {}

        void fit(const Eigen::ArrayXXd& X, const Eigen::ArrayXd& y);
        Eigen::ArrayXd& predict(const Eigen::ArrayXXd& X);
};

#endif
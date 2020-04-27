#ifndef KNN_CLASSIFIER
#define KNN_CLASSIFIER

#include <Eigen/Dense>
#include "base.h"
#include <map>

using namespace Eigen;

class KNeighborsClassifier: public ClassifierMixin{
    public:
        map<string, prm> test;

        int& n_neighbors;
        string& weights;
        ArrayXXd X_;
        ArrayXd y_;
    
        KNeighborsClassifier(int n_neighbors=5, string weights="uniform");
        ~KNeighborsClassifier() {}

        void fit(const ArrayXXd& X, const ArrayXd& y);
        ArrayXd predict(const ArrayXXd& X);
};

#endif
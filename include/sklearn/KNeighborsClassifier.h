#ifndef KNN_CLASSIFIER
#define KNN_CLASSIFIER

#include <Eigen/Dense>
#include "base.h"
#include <map>

using namespace Eigen;

ArrayXi n_argmax(ArrayXd& array, const int& N);

class KNeighborsClassifier: public ClassifierMixin{
    public:
        int& n_neighbors;
        string& weights;

        ArrayXXd X_;
        ArrayXd y_;
    
        KNeighborsClassifier(int n_neighbors=5, string weights="uniform");
        ~KNeighborsClassifier() {}

        void fit(const ArrayXXd& X, const ArrayXd& y);
        ArrayXd predict(const ArrayXXd& X);
        virtual KNeighborsClassifier* clone() const{
            return new KNeighborsClassifier(*this);
        }
};

#endif
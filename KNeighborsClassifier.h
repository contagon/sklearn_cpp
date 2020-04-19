#ifndef KNN_CLASSIFIER
#define KNN_CLASSIFIER

#include <Eigen/Dense>
#include "base.h"

// // helper function
// ArrayXd n_argmax(ArrayXd& array, const int& N){
//     // make array of indices
//     ArrayXd indices = ArrayXd::LinSpaced(array.size(),0,array.size()-1);

//     //partial_sort indice array
//     std::partial_sort(indices.data(), indices.data()+N, indices.data()+indices.size(),
//                      [&array](int i,int j) {return array[i]<array[j];});

//     return indices.head(N);
// }

class KNeighborsClassifier: public ClassifierMixin{
    public:
        int n_neighbors;
        Eigen::ArrayXXd X_;
        Eigen::ArrayXd y_;
    
        KNeighborsClassifier(int n_neighbors=5);
        ~KNeighborsClassifier() {}

        void fit(const Eigen::ArrayXXd& X, const Eigen::ArrayXd& y);
        Eigen::ArrayXd predict(const Eigen::ArrayXXd& X);
};

#endif
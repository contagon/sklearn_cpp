#include "KNeighborsClassifier.h"

// Default Constructor
KNeighborsClassifier::KNeighborsClassifier(int n_neighbors) : n_neighbors(n_neighbors) {}

void KNeighborsClassifier::fit(const Eigen::ArrayXXd& X, const Eigen::ArrayXd& y){
    this->X = X;
    this->y = y;
} 

Eigen::ArrayXd& KNeighborsClassifier::predict(const Eigen::ArrayXXd& X){
    // TODO HERE
    return this->y;
}

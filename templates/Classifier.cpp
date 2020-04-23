#include "Classifier.h"

// Default Constructor
Classifier::Classifier() {}

void Classifier::fit(const ArrayXXd& X, const ArrayXd& y){
    // Make sure everything is in order
    check_X_y(X, y);
} 

ArrayXd Classifier::predict(const ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

}

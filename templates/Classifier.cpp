#include "Classifier.h"

// Default Constructor
Classifier::Classifier(int fake_param) 
        : BaseEstimator({{"fake_param", fake_param}}), 
        fake_param(get<int>(params["fake_param"]) {}
        // The actual value is saved in the base class map
        // But we make a reference to it to make syntax easier throughout our class


void Classifier::fit(const ArrayXXd& X, const ArrayXd& y){
    // Make sure everything is in order
    check_X_y(X, y);
} 

ArrayXd Classifier::predict(const ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

}

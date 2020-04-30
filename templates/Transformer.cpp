#include "Transfomer.h"

// Default Constructor
Transfomer::Transfomer(int fake_param) 
        : BaseEstimator({{"fake_param", fake_param}}), 
        fake_param(get<int>(params["fake_param"]) {}
        // The actual value is saved in the base class map
        // But we make a reference to it to make syntax easier throughout our class

void Transfomer::fit(ArrayXXd X){
    // Make sure everything is in order
    check_X_y(X);
} 

void Transfomer::transform_inplace(ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);
}

void Transfomer::inverse_transform_inplace(ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X); // May need to remove this if doing some sort of dimension reduction
}

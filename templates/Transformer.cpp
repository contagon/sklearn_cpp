#include "Transfomer.h"

// Default Constructor
Transfomer::Transfomer() {}

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

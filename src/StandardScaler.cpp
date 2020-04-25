#include "StandardScaler.h"

// Default Constructor
StandardScaler::StandardScaler(bool with_mean, bool with_std) 
                : with_mean(with_mean), with_std(with_std) {}

void StandardScaler::fit(ArrayXXd X){
    // Make sure everything is in order
    check_X_y(X);

    // Calculate mean and variance
    mean_ = X.colwise().mean();

    var_ = ArrayXd( n_features() );
    for(int i=0; i<n_features(); i++)
        var_(i) = (X.col(i) - mean_(i)).square().sum() / (X.rows() - 1);

    scale_ = var_.sqrt();
} 

void StandardScaler::transform_inplace(ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

    if(with_mean)
        X.rowwise() -= mean_.transpose();

    if(with_std)
        X.rowwise() /= scale_.transpose();
}

void StandardScaler::inverse_transform_inplace(ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

    if(with_std)
        X.rowwise() *= scale_.transpose();

    if(with_mean)
        X.rowwise() += mean_.transpose();
}

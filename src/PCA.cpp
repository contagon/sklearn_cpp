#include "PCA.h"

// Default Constructor
PCA::PCA(int n_components, bool center) 
                : n_components(n_components), center(center) {}

void PCA::fit(ArrayXXd X){
    // Make sure everything is in order
    check_X_y(X);
    if(n_components > n_features_)
        throw std::invalid_argument( "n_components is larger than n_features" );

    //Center it first if requested
    if(center){
        mean_ = X.colwise().mean();
        X.rowwise() -= mean_.transpose();
    }

    // Compute SVD and split as needed
    BDCSVD<MatrixXd> svd(X, ComputeThinU | ComputeThinV);
    V_ = svd.matrixV()(all, seq(0, n_components-1));
    explained_variance_ = svd.singularValues().array().square() / (X.rows()-1);
    explained_variance_ratio_ = explained_variance_ / explained_variance_.sum();
} 

void PCA::transform_inplace(ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

    //Center it first if requested
    if(center)
        X.rowwise() -= mean_.transpose();
    
    // Perform operation
    X.matrix() *= V_.matrix();
}

void PCA::inverse_transform_inplace(ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();

    // Perform operation
    X.matrix() *= V_.transpose().matrix();

    //Center it first if requested
    if(center)
        X.rowwise() += mean_.transpose();
}
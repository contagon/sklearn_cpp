#include "MinMaxScaler.h"

// Default Constructor
MinMaxScaler::MinMaxScaler(float feature_min, float feature_max) 
    : BaseEstimator({{"feature_min", feature_min},{"feature_max", feature_max}}),
    feature_min(get<float>(params["feature_min"])), 
    feature_max(get<float>(params["feature_max"])) {}

void MinMaxScaler::fit(ArrayXXd X){
    // Make sure everything is in order
    check_X_y(X);

    // Calculate values
    data_min_ = X.colwise().minCoeff();
    data_max_ = X.colwise().maxCoeff();
    scale_ = (feature_max - feature_min) / (data_max_ - data_min_);
    min_ = feature_min - data_min_ * scale_;
} 

void MinMaxScaler::transform_inplace(ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

    X.rowwise() *= scale_.transpose();
    X.rowwise() += min_.transpose();
}

void MinMaxScaler::inverse_transform_inplace(ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

    X.rowwise() -= min_.transpose();
    X.rowwise() /= scale_.transpose();
}

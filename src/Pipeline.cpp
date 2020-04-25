#include "Pipeline.h"

// Default Constructor
Pipeline::Pipeline(vector<BaseEstimator*> estimators) 
        : estimators(estimators) {}

Pipeline::~Pipeline(){
    for (auto estimator : estimators)
        delete estimator;

    estimators.clear();
}


/////// Methods if we end with an Estimator

void Pipeline::fit(ArrayXXd X, const ArrayXd& y){
    // Make sure everything is in order
    check_X_y(X, y);

    for(int i=0; i<estimators.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*estimators[i]).fit_transform_inplace(X);

    return dynamic_cast<EstimatorMixin&>(*estimators.back()).fit(X, y);
} 

ArrayXd Pipeline::predict(ArrayXXd X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

    for(int i=0; i<estimators.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*estimators[i]).transform_inplace(X);

    return dynamic_cast<EstimatorMixin&>(*estimators.back()).predict(X);
}

float Pipeline::score(ArrayXXd X, const ArrayXd& y){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

    for(int i=0; i<estimators.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*estimators[i]).transform_inplace(X);

    return dynamic_cast<EstimatorMixin&>(*estimators.back()).score(X, y);
}


////// Methods if they're all transformers

void Pipeline::fit(ArrayXXd X){
    // Make sure everything is in order
    check_X_y(X);

    for(auto estimator : estimators)
        dynamic_cast<TransformerMixin&>(*estimator).fit(X);
} 

void Pipeline::transform_inplace(ArrayXXd& X){
    // Make sure everything is in order
    check_is_fitted();
    check_X(X);

    for(auto estimator : estimators)
        dynamic_cast<TransformerMixin&>(*estimator).transform_inplace(X);
}

void Pipeline::inverse_transform_inplace(ArrayXXd& X){
    // Make sure everything is in order
    check_is_fitted();

    for (auto estimator=estimators.rbegin(); estimator!=estimators.rend(); ++estimator)
        dynamic_cast<TransformerMixin&>(**estimator).inverse_transform_inplace(X);
}
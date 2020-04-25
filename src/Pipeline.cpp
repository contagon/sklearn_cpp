#include "Pipeline.h"

// Default Constructor
Pipeline::Pipeline(vector<pair<string, BaseEstimator*>> estimators) 
        : estimators(estimators) {}

Pipeline::~Pipeline(){
    for (auto [name, estimator] : estimators)
        delete estimator;

    estimators.clear();
}


/********************************************************
*********    Methods if we end with an Estimator    *****
*********************************************************/

void Pipeline::fit(const ArrayXXd& X, const ArrayXd& y){
    // Make sure everything is in order
    check_X_y(X, y);
    ArrayXXd Xcopy = X;

    for(int i=0; i<estimators.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*estimators[i].second).fit_transform_inplace(Xcopy);

    dynamic_cast<EstimatorMixin&>(*estimators.back().second).fit(Xcopy, y);
} 

ArrayXd Pipeline::predict(const ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);
    ArrayXXd Xcopy = X;

    for(int i=0; i<estimators.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*estimators[i].second).transform_inplace(Xcopy);

    return dynamic_cast<EstimatorMixin&>(*estimators.back().second).predict(Xcopy);
}

float Pipeline::score(const ArrayXXd& X, const ArrayXd& y){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);
    ArrayXXd Xcopy = X;

    for(int i=0; i<estimators.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*estimators[i].second).transform_inplace(Xcopy);

    return dynamic_cast<EstimatorMixin&>(*estimators.back().second).score(Xcopy, y);
}


/********************************************************
*********   Methods if we end with an Transformer   *****
*********************************************************/

void Pipeline::fit(ArrayXXd X){
    // Make sure everything is in order
    check_X_y(X);

    for(auto [name, estimator] : estimators)
        dynamic_cast<TransformerMixin&>(*estimator).fit(X);
} 

void Pipeline::transform_inplace(ArrayXXd& X){
    // Make sure everything is in order
    check_is_fitted();
    check_X(X);

    for(auto const& [name, estimator] : estimators)
        dynamic_cast<TransformerMixin&>(*estimator).transform_inplace(X);
}

void Pipeline::inverse_transform_inplace(ArrayXXd& X){
    // Make sure everything is in order
    check_is_fitted();

    for (auto estimator=estimators.rbegin(); estimator!=estimators.rend(); ++estimator)
        dynamic_cast<TransformerMixin&>(*(*estimator).second).inverse_transform_inplace(X);
}



/********************************************************
*********               Indexing Methods            *****
*********************************************************/
BaseEstimator& Pipeline::operator[](string goal_name){
    // Do naive search through estimators
    for(auto const& [name, estimator] : estimators){
        if(name == goal_name)
            return *estimator;
    }
}
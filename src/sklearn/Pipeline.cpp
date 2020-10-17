#include "sklearn/Pipeline.h"
#include <iostream>
#include <typeinfo>

/********************************************************
*********             Overriding Methods            *****
*********************************************************/
Pipeline::Pipeline(vector<pair<string, BaseEstimator*>> steps) 
        : steps(steps) {}

Pipeline::~Pipeline(){
    for (auto [name, step] : steps)
        delete step;

    steps.clear();
}

Pipeline::Pipeline(const Pipeline& other){
    for(auto [name, step] : other.steps){
        BaseEstimator* temp = step->clone();
        this->steps.push_back( make_pair(name, temp) );
    }
}
Pipeline& Pipeline::operator=(const Pipeline& rhs){
    Pipeline copy(rhs);

    // Delete current values
    for (auto [name, step] : steps)
        delete step;
    steps.clear();

    // Assign to copy ones
    this->steps = copy.steps;

    return *this;
}


/********************************************************
*********    Methods if we end with an Estimator    *****
*********************************************************/

void Pipeline::fit(const ArrayXXd& X, const ArrayXd& y){
    // Make sure everything is in order
    check_X_y(X, y);
    ArrayXXd Xcopy = X;

    for(int i=0; i<steps.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*steps[i].second).fit_transform_inplace(Xcopy);

    dynamic_cast<EstimatorMixin&>(*steps.back().second).fit(Xcopy, y);
} 

ArrayXd Pipeline::predict(const ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);
    ArrayXXd Xcopy = X;

    for(int i=0; i<steps.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*steps[i].second).transform_inplace(Xcopy);

    return dynamic_cast<EstimatorMixin&>(*steps.back().second).predict(Xcopy);
}

float Pipeline::score(const ArrayXXd& X, const ArrayXd& y){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);
    ArrayXXd Xcopy = X;

    for(int i=0; i<steps.size()-1;i++)
        dynamic_cast<TransformerMixin&>(*steps[i].second).transform_inplace(Xcopy);

    return dynamic_cast<EstimatorMixin&>(*steps.back().second).score(Xcopy, y);
}


/********************************************************
*********   Methods if we end with an Transformer   *****
*********************************************************/

void Pipeline::fit(ArrayXXd X){
    // Make sure everything is in order
    check_X_y(X);

    for(auto [name, step] : steps)
        dynamic_cast<TransformerMixin&>(*step).fit(X);
} 

void Pipeline::transform_inplace(ArrayXXd& X){
    // Make sure everything is in order
    check_is_fitted();
    check_X(X);

    for(auto const& [name, step] : steps)
        dynamic_cast<TransformerMixin&>(*step).transform_inplace(X);
}

void Pipeline::inverse_transform_inplace(ArrayXXd& X){
    // Make sure everything is in order
    check_is_fitted();

    for (auto step=steps.rbegin(); step!=steps.rend(); ++step)
        dynamic_cast<TransformerMixin&>(*(*step).second).inverse_transform_inplace(X);
}



/********************************************************
*********               Indexing Methods            *****
*********************************************************/
BaseEstimator* Pipeline::operator[](string goal_name){
    // Do naive search through steps
    for(auto const& [name, step] : steps){
        if(name == goal_name)
            return step;
    }
    throw invalid_argument( "Not a valid step name" );
}
BaseEstimator* Pipeline::operator[](int idx){
    return steps[idx].second;
}
Pipeline Pipeline::operator()(int start, int stop){
    // check to make sure things are in range
    if(start < 0) throw invalid_argument("Lower index is too low");
    if(stop > steps.size()) throw invalid_argument("Upper index is too high");
    // Make copy of itself
    Pipeline subpipe(*this);

    // Basically just clear portion that we don't want
    vector<pair<string, BaseEstimator*>> substep;
    int i = 0;
    for(auto [name, step] : subpipe.steps){
        if(start <= i && i < stop)
            substep.push_back( make_pair(name, step) );
        else
            delete step;
        i++;
    }
    subpipe.steps = substep;
    return subpipe;
}


/********************************************************
*********         Getting/Setting Params            *****
*********************************************************/
void Pipeline::set_params(map<string,prm> new_params){
    // Make a map for each step with it's params
    map<string,map<string,prm>> step_params;
    for(auto [name, param] : new_params){
        string step_name = name.substr(0, name.find("__"));
        string param_name = name.substr(name.find("__")+2, name.size());
        step_params[step_name][param_name] = param;
    }

    // Apply them to each step
    for( auto [name, step] : steps){
        step->set_params(step_params[name]);
    }
}

map<string, prm> Pipeline::get_params(){
    map<string, prm> all_params;
    for(auto [step_name, step] : steps){
        for(auto [param_name, param] : step->get_params()){
            all_params[ step_name + "__" + param_name] = param;
        }
    }
    return all_params;
}

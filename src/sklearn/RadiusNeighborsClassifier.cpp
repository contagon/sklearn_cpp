#include "RadiusNeighborsClassifier.h"

// Default Constructor
RadiusNeighborsClassifier::RadiusNeighborsClassifier(float radius, string weights) 
    : BaseEstimator({{"radius", weights},{"feature_max", weights}}),
    radius(get<float>(params["radius"])), 
    weights(get<string>(params["weights"])) {}

void RadiusNeighborsClassifier::fit(const ArrayXXd& X, const ArrayXd& y){
    check_X_y(X, y);
    this->X_ = X;
    this->y_ = y;
} 

ArrayXd RadiusNeighborsClassifier::predict(const ArrayXXd& X){
    // Check to make sure everything is in order
    check_is_fitted();
    check_X(X);

    ArrayXd prediction(X.rows()); 
    int i = 0;
    for(auto x: X.rowwise()){
        // Get distance for point from all other points
        ArrayXd distance = (X_.rowwise() - x).rowwise().squaredNorm();

        // Get all idxs under radius
        Array<bool, Dynamic, 1> mask = distance < radius;
        ArrayXi idxs = ArrayXi::Zero(mask.count());
        // Extract idxs from mask
        int j = 0;
        int k = 0;
        for(auto m : mask){
            if(m){
                idxs(j) = k;
                j++;
            }
            k++;
        }
        // Give weights to each label
        map<double, int> counter;
        for(auto idx: idxs)
        {
            if(weights == "uniform")
                counter[y_(idx)] += 1;
            else if(weights == "distance")
                counter[y_(idx)] += 1 / distance(idx);
        }
        // Get most largest weighted label
        prediction(i) = (*max_element(counter.begin(), counter.end(),
            [](const pair<double, int>& p1, const pair<double, int>& p2) {
                return p1.second < p2.second; })).first;
        i++;
    }
    return prediction;
}

#include "KNeighborsClassifier.h"

ArrayXi n_argmax(ArrayXd& array, const int& N){
    // make array of indices
    ArrayXi indices = ArrayXi::LinSpaced(array.size(),0,array.size()-1);

    //partial_sort indice array
    std::partial_sort(indices.data(), indices.data()+N, indices.data()+indices.size(),
                     [&array](int i,int j) {return array[i]<array[j];});

    return indices.head(N);
}

// Default Constructor
KNeighborsClassifier::KNeighborsClassifier(int n_neighbors, string weights) 
                : n_neighbors(n_neighbors), weights(weights) {}

void KNeighborsClassifier::fit(const Eigen::ArrayXXd& X, const Eigen::ArrayXd& y){
    this->X_ = X;
    this->y_ = y;
} 

Eigen::ArrayXd KNeighborsClassifier::predict(const Eigen::ArrayXXd& X){
    ArrayXd prediction(X.rows()); 
    int i = 0;
    for(auto x: X.rowwise()){
        // Get distance for point from all other points
        ArrayXd distance = (X_.rowwise() - x).rowwise().squaredNorm();

        // Get closests N indices
        ArrayXi idxs = n_argmax(distance, n_neighbors);

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
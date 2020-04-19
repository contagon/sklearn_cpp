//Header file for input output functions 
#include "hdf5.hpp"
#include <Eigen/Dense>
#include <iostream>  
#include <numeric>

#include "KNeighborsClassifier.h"

using namespace Eigen;
using namespace std; 


// ArrayXd n_argmax(ArrayXd& array, const int& N){
//     // make array of indices
//     ArrayXd indices = ArrayXd::LinSpaced(array.size(),0,array.size()-1);

//     //partial_sort indice array
//     std::partial_sort(indices.data(), indices.data()+N, indices.data()+indices.size(),
//                      [&array](int i,int j) {return array[i]<array[j];});

//     return indices.head(N);
// }

int main() 
{ 

	HDF5::File hf = HDF5::File("../data/digits.h5", HDF5::File::ReadOnly);

    Eigen::MatrixXd X;
    Eigen::VectorXd y;
    Eigen::VectorXd y_predict;


    hf.read("X", X);
    hf.read("y", y);
    for(int i=1; i<=15; i+=2){
        KNeighborsClassifier knn(i);
        // cout  << "Fitting... \n";
        knn.fit(X, y);
        // cout << "Scoring... \n";
        cout << i << ": " << knn.score(X, y) << "\n";
    }
    
	return 0; 
} 

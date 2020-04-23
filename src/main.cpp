//Header file for input output functions 
#include "hdf5.hpp"
#include <Eigen/Dense>
#include <iostream>  

#include "KNeighborsClassifier.h"
#include "RadiusNeighborsClassifier.h"

#include "PCA.h"
#include "StandardScaler.h"
#include "MinMaxScaler.h"

#include "model_selection.h"

using namespace Eigen;
using namespace std; 


int main() 
{ 

	HDF5::File hf = HDF5::File("../data/iris.h5", HDF5::File::ReadOnly);
    Eigen::MatrixXd X;
    Eigen::VectorXd y;
    Eigen::VectorXd y_predict;
    hf.read("X", X);
    hf.read("y", y);

    ArrayXXd Xc = X;
    cout << Xc.row(1) << endl;
    cout << Xc.colwise().mean() << endl << endl;
    PCA trans(2);
    trans.fit_transform_inplace(Xc);
    cout << Xc.row(1) << endl;
    cout << Xc.colwise().mean() << endl;
    trans.inverse_transform_inplace(Xc);
    cout << Xc.row(1) << endl;
    cout << Xc.colwise().mean() << endl;
    cout << trans.V_.transpose().matrix() * trans.V_.matrix() << endl;
    
    // auto data = test_train_split(X, y, 0.3333, false);
    // for(int i=1; i<=25; i+=2){
    //     RadiusNeighborsClassifier knn(float(i)/10, "distance");
    //     // cout  << "Fitting... \n";
    //     knn.fit(data.X_train, data.y_train);
    //     // cout << "Scoring... \n";
    //     cout << float(i)/10 << ": " << knn.score(data.X_test, data.y_test) << "\n";
    // }

	return 0; 
} 

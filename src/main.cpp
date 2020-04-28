//Header file for input output functions 
#include "hdf5.hpp"
#include <Eigen/Dense>
#include <iostream>  
#include "base.h"

#include "KNeighborsClassifier.h"
#include "RadiusNeighborsClassifier.h"

#include "PCA.h"
#include "StandardScaler.h"
#include "MinMaxScaler.h"

#include "model_selection.h"
#include "Pipeline.h"

#include <vector>
#include <map>

using namespace Eigen;
using namespace std; 

int main() 
{ 
    // Read data
	HDF5::File hf = HDF5::File("../data/iris.h5", HDF5::File::ReadOnly);
    Eigen::MatrixXd X;
    Eigen::VectorXd y;
    Eigen::VectorXd y_predict;
    hf.read("X", X);
    hf.read("y", y);
    auto [X_train, X_test, y_train, y_test] = test_train_split(X, y, 0.3333, true);

    //  """ Pipeline Testing """
    //  Can't do subpipe like this, no way to properly delete pointer
    Pipeline pipe1 = Pipeline({{"pca", new PCA(2)}});
    Pipeline pipe({  {"pipe", &pipe1 },
                 {"knn", new KNeighborsClassifier(5)}});
    
    pipe.fit(X,y);
    Pipeline subpipe = pipe(0,1);
    
    

    // """ Transformer Testing """
    // ArrayXXd Xc = X;
    // Pipeline trans({new StandardScaler, new PCA(4)});
    // trans.fit(X);
    // cout << Xc.row(1) << endl;
    // trans.transform_inplace(Xc);
    // cout << Xc.row(1) << endl;
    // trans.inverse_transform_inplace(Xc);
    // cout << Xc.row(1) << endl;
    
    // """ Estimator Testing """
    // for(int i=1; i<=15; i+=2){
    //     KNeighborsClassifier knn(i);
    //     // cout  << "Fitting... \n";
    //     knn.fit(X_train, y_train);
    //     // cout << "Scoring... \n";
    //     cout << float(i) << ": " << knn.score(X_test, y_test) << "\n";
    // }

	return 0; 
} 



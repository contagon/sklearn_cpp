//Header file for input output functions 
#include "hdf5.hpp"
#include <Eigen/Dense>
#include <iostream>  
#include "sklearn/base.h"

#include "sklearn/KNeighborsClassifier.h"
#include "sklearn/RadiusNeighborsClassifier.h"

#include "sklearn/PCA.h"
#include "sklearn/StandardScaler.h"
#include "sklearn/MinMaxScaler.h"

#include "sklearn/model_selection.h"
#include "sklearn/Pipeline.h"

#include <vector>
#include <map>

using namespace Eigen;
using namespace std; 

int main() 
{ 
    cout << "I compiled!" << endl;


    // Read data
	// HDF5::File hf = HDF5::File("../data/iris.h5", HDF5::File::ReadOnly);
    // Eigen::MatrixXd X;
    // Eigen::VectorXd y;
    // Eigen::VectorXd y_predict;
    // hf.read("X", X);
    // hf.read("y", y);
    // auto [X_train, X_test, y_train, y_test] = test_train_split(X, y, 0.3333, true);

    //  """ Pipeline Testing """
    //  Can't do subpipe like this, no way to properly delete pointer
    Pipeline pipe1 = Pipeline({{"pca", new PCA(2)}});
    // Pipeline pipe({  {"pipe", &pipe1 },
                //  {"knn", new KNeighborsClassifier(5)}});
    
    // PCA* pca = new PCA(3);
    // BaseEstimator* be = new PCA(2);
    // *be = *pca;
    // cout << typeid(dynamic_cast<TransformerMixin&>(*be)).name() << endl;
    
    // Pipeline pipe2({{"pca", new PCA(10)}, {"knn", new KNeighborsClassifier(5)}});
    // cout << pipe2["knn"].is_fitted() << endl;
    // pipe2.fit(X_train, y_train);
    // cout << pipe2["knn"].is_fitted() << endl;
    // cout << pipe2.score(X_test, y_test) << endl;

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



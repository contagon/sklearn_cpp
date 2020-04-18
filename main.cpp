//Header file for input output functions 
#include "hdf5.hpp"
#include <Eigen/Dense>
#include <iostream>  

#include "KNeighborsClassifier.h"

using namespace std; 

// main function - 
// where the execution of program begins 
int main() 
{ 
	// prints hello world 
	// cout << "Hello World" << endl; 
	// cout << "It's all starting to come back!" << endl; 

	// Eigen::Matrix<double,3,3> m;
	// m << 5,0,0, 0,1,0, 0,0,1;

	// Eigen::Vector3d v;
	// v << 1,-2,3;
	// cout << m*v << endl;
	// cout << m.size() << endl;

	// write_data();
	// read_data();

	HDF5::File hf = HDF5::File("../data/iris.h5", HDF5::File::ReadOnly);

    Eigen::MatrixXd X;
    Eigen::VectorXd y;
    Eigen::VectorXd y_predict;


    hf.read("X", X);
    hf.read("y", y);
    
    KNeighborsClassifier knn(10);

    knn.fit(X, y);
    y[10] = 10;
    cout << knn.score(X, y);

	return 0; 
} 

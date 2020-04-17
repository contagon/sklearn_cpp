//Header file for input output functions 
#include "hdf5.hpp"
#include <Eigen/Dense>
#include <iostream>  

using namespace std; 

void write_data() {
    Eigen::MatrixXd matrix(3, 3);
    matrix << 1, 2, 3, 4, 5, 6, 7, 8, 11;

    // open the file 
    HDF5::File hf = HDF5::File("filename.hdf5", HDF5::File::Truncate);

    // write the data
    hf.write("dataset_name", matrix);
    
    std::cout << "Original Matrix: " << std::endl;
    std::cout << matrix << std::endl;
}

void read_data() {
    // open the file for reading
    HDF5::File hf = HDF5::File("filename.hdf5", HDF5::File::ReadOnly);

    Eigen::MatrixXd matrix;

    hf.read("dataset_name", matrix);
    
    std::cout << "Matrix read: " << std::endl;
    std::cout << matrix << std::endl;
}

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


    hf.read("X", X);
    hf.read("y", y);
    
    std::cout << "Matrix read: " << std::endl;
    std::cout << X << std::endl;
    std::cout << y << std::endl;

	return 0; 
} 

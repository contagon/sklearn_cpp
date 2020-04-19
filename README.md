Summer Project to freshen up on my C++ skills. Seeking to implement various sklearn algorithms in C++.

## Implemented Algorithms
  * kNeighborsClassifier

## Dependencies
  * [Eigen](https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html): C++ Numpy Equivalent. [Installation](https://eigen.tuxfamily.org/dox/GettingStarted.html) (or available via apt)
  * [fdcl-hdf5](https://github.com/skulumani/fdcl-hdf5): Used to save eigen data to HD5 files. [Installation](https://shankarkulumani.com/2018/09/hdf5.html).

## Resources
  * [C++ Tutorials](https://github.com/mhask94/cpp_tutorials). I've been following these to get used to cmake and eigen. Made by Matt Haskell here at BYU.
  * [Eigen Reference Sheet](https://gist.github.com/gocarlos/c91237b02c120c6319612e42fa196d77)
  
Note to get fdcl-hdf5 to find the hdf5 libraries, I add to run `export CPATH=/usr/include/hdf5/serial/` or add it to my bashrc.

Had issues finding a library installed with anaconda, adding `export LD_LIBRARY_PATH=/home/contagon/anaconda3/lib:$LD_LIBRARY_PATH` did the trick.

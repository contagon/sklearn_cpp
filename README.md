Summer Project to freshen up on my C++ skills. Seeking to implement various sklearn algorithms in C++.

## Implemented Algorithms
| Transformers | Classifiers | Regressors | Misc|
|:----:|:----:|:----:|:----:|
| PCA |kNeighborsClassifier|  | Test-Train Split |
| StandardScaler |RadiusNeighborsClassifier| | Pipeline |
| MinMaxScaler | | | |

## Dependencies
  * [Eigen](https://eigen.tuxfamily.org/dox/group__TutorialMatrixArithmetic.html): C++ Numpy Equivalent. [Installation](https://eigen.tuxfamily.org/dox/GettingStarted.html). NEED at least version 3.3.90 which is currently the newest version available (have to clone master branch of eigen). It has various improvements, most importantly MUCH improved slicing capability.
  * [fdcl-hdf5](https://github.com/skulumani/fdcl-hdf5)(optional): Used to save and load HD5 files. [Installation](https://shankarkulumani.com/2018/09/hdf5.html).

## Resources
  * [C++ Tutorials](https://github.com/mhask94/cpp_tutorials). I've been following these to get used to cmake and eigen. Made by Matt Haskell here at BYU.
  * [Eigen Reference Sheet](https://gist.github.com/gocarlos/c91237b02c120c6319612e42fa196d77)
  * [CMake Tutorial](http://derekmolloy.ie/hello-world-introductions-to-cmake/)
  * [GTest Introduction](https://chromium.googlesource.com/external/github.com/google/googletest/+/refs/tags/release-1.8.0/googletest/docs/Primer.md)
  
Note to get fdcl-hdf5 to find the hdf5 libraries, I add to run `export CPATH=/usr/include/hdf5/serial/` or add it to my bashrc.

Had issues finding a library installed with anaconda, running `sudo ln -s "$HOME/anaconda3/lib/libhdf5.so.103" "/usr/lib/x86_64-linux-gnu/libhdf5.so.103"` did the trick.

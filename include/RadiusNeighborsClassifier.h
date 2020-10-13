#ifndef RN_CLASSIFIER
#define RN_CLASSIFIER

#include "base.h"
#include <Eigen/Dense>
#include <map>

using namespace Eigen;

class RadiusNeighborsClassifier : public ClassifierMixin {
public:
  float &radius;
  string &weights;

  ArrayXXd X_;
  ArrayXd y_;

  RadiusNeighborsClassifier(float radius = 1, string weights = "uniform");
  ~RadiusNeighborsClassifier() {}

  void fit(const ArrayXXd &X, const ArrayXd &y);
  ArrayXd predict(const ArrayXXd &X);
  virtual RadiusNeighborsClassifier *clone() const {
    return new RadiusNeighborsClassifier(*this);
  }
};

#endif
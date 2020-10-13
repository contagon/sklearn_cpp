#ifndef CLASSIFIER
#define CLASSIFIER

#include "base.h"
#include <Eigen/Dense>

using namespace Eigen;

class Classifier : public ClassifierMixin {
public:
  // This reference param is 100% not needed, but can be used for convenience
  int &fake_param;

  Classifier(int fake_param);
  ~Classifier() {}

  void fit(const ArrayXXd &X, const ArrayXd &y);
  ArrayXd predict(const ArrayXXd &X);
  virtual Classifier *clone() const { return new Classifier(*this); }
};

#endif
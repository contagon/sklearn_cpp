#ifndef TRANSFORMER
#define TRANSFORMER

#include "base.h"
#include <Eigen/Dense>

using namespace Eigen;

class Transfomer : public TransformerMixin {
public:
  // This reference param is 100% not needed, but can be used for convenience
  int &fake_param;

  Transfomer(int fake_param);
  ~Transfomer() {}

  void fit(ArrayXXd X);
  void transform_inplace(ArrayXXd &X);
  void inverse_transform_inplace(ArrayXXd &X);
  virtual Transfomer *clone() const { return new Transfomer(*this); }
};

#endif
#ifndef PCA_DEF
#define PCA_DEF

#include "base.h"
#include <Eigen/Dense>

using namespace Eigen;

class PCA : public TransformerMixin {
public:
  int &n_components;
  bool &center;

  ArrayXXd V_;
  ArrayXd explained_variance_;
  ArrayXd explained_variance_ratio_;
  ArrayXd mean_;

  PCA(int n_components, bool center = true);
  ~PCA() {}

  void fit(ArrayXXd X);
  void transform_inplace(ArrayXXd &X);
  void inverse_transform_inplace(ArrayXXd &X);
  virtual PCA *clone() const { return new PCA(*this); }
};

#endif
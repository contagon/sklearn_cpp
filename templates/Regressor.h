#ifndef REGRESSOR
#define REGRESSOR

#include <Eigen/Dense>
#include "base.h"

using namespace Eigen;

class Regressor: public RegressorMixin{
    public:
        // This reference param is 100% not needed, but can be used for convenience 
        int& fake_param;

        Regressor(int fake_param);
        ~Regressor() {}

        void fit(const ArrayXXd& X, const ArrayXd& y);
        ArrayXd predict(const ArrayXXd& X);
        virtual Regressor* clone() const{
            return new Regressor(*this);
        }
};

#endif
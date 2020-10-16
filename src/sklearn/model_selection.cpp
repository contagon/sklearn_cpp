#include "model_selection.h"

Split test_train_split(const ArrayXXd& X, const ArrayXd& y, float test_size, bool shuffle){
    // get number of items in test set
    int test_num = floor( test_size * X.rows() );

    // make indices and shuffle them
    ArrayXd idx = ArrayXd::LinSpaced(y.size(),0,y.size()-1);
    if(shuffle)
        random_shuffle(idx.data(), idx.data()+idx.size());

    // Split indices
    ArrayXd test_idx = idx( seq(0, test_num) );
    ArrayXd train_idx = idx( seq(test_num+1, last) );

    // Put into struct and return
    return Split{X(train_idx, all), X(test_idx, all), y(train_idx), y(test_idx)};
}
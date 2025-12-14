#include <cml/ml.h>

int main()
{
    f64 input[] = {
        0,1,2,3
    };

    f64 output[] = {
        0,105,210,315
    };

    f64 x_pred[] = {
        100
    };

    CML_Hyperparams hyperparams = {
        .lambda = 20 * 0.01,
        .learning_rate = 0.1,
        .training_count = 1000 * 1
    };

    CML_CLinearRegression *lasso = CML_CLinearRegression_init(hyperparams);
    lasso->fit(lasso,input,1,output,CML_ARRAY_LEN(output));
    f64 y_pred = lasso->predict(lasso,x_pred,1);
    lasso->print(lasso);
    CML_CLinearRegression_fini(lasso);
    CML_PRINTF("%lf\n",y_pred);
}

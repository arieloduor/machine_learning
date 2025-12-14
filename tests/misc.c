#include <cml/ml.h>

int main()
{
    f64 x[] = {
        0,0,
        1,2,
        2,4,
        3,6,
        4,8,
        5,10,
        6,12,
        7,14,
        8,16,
        9,18,
        10,20,
        11,22,
        12,24,
        13,26,
        15,30,
        16,32,
        17,34,
    };

    f64 pred[] = {
        14
    };

    CML_Hyperparams hyperparams = {
        .neighbors = 3,
    };



    CML_CKNNRegression *knn = CML_CKNNRegression_init(hyperparams);
    f64 y = knn->predict(knn,x,1,16,pred);
    CML_CKNNRegression_fini(knn);
    CML_PRINTF("[14] => %lf\n",y);
}



int main4()
{
    f64 x[] = {
        2,10,2,
        2,6,1,
        11,11,3,
        6,9,2,
        6,5,1,
        1,2,1,
        5,10,2,
        4,9,2,
        10,12,3,
        7,5,1,
        9,11,3,
        4,6,1,
        3,10,2,
        3,8,2,
        6,11,2
    };

    f64 pred[] = {
        5,7
    };

    CML_Hyperparams hyperparams = {
        .neighbors = 3,
    };



    CML_CKNNClassifier *knn = CML_CKNNClassifier_init(hyperparams);
    f64 y = knn->predict(knn,x,2,15,2,pred);
    CML_CKNNClassifier_fini(knn);
    if(y == 1)
        CML_PRINTF("C1\n");
    else if(y == 2)
        CML_PRINTF("C2\n");
    else
        CML_PRINTF("C3\n");
}


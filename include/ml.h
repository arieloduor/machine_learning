#ifndef CML_ML_H
#define CML_ML_H



#include "vector.h"

typedef struct CML_Hyperparams
{
    f64 learning_rate;
    u64 training_count;
    u64 lambda;
    u64 neighbors;
}CML_Hyperparams;




typedef struct CML_CLinearRegression
{
    CML_Hyperparams hyperparams;
    CML_ACVec *acvec;
    CML_Vec weight_vec;
    void (*fit)(void *self,f64 *input_X,u64 inputsize,f64 *output_Y,u64 outputsize);
    f64 (*predict)(void *self,f64 *input_X,u64 inputsize);
    void (*print)(void *self);
}CML_CLinearRegression;




CML_CLinearRegression *CML_CLinearRegression_init(CML_Hyperparams hyperparams); 

void CML_CLinearRegression_fini(CML_CLinearRegression *linear);





typedef struct CML_CLassoRegression
{
    CML_Hyperparams hyperparams;
    CML_ACVec *acvec;
    CML_Vec weight_vec;
    void (*fit)(void *self,f64 *input_X,u64 inputsize,f64 *output_Y,u64 outputsize);
    f64 (*predict)(void *self,f64 *input_X,u64 inputsize);
    void (*print)(void *self);
}CML_CLassoRegression;



CML_CLassoRegression *CML_CLassoRegression_init(CML_Hyperparams hyperparams); 

void CML_CLassoRegression_fini(CML_CLassoRegression *lasso);





typedef struct CML_CKNNRegression
{
    CML_Hyperparams hyperparams;
    CML_ACVec *acvec;
    f64 (*predict)(void *self,f64 *input,u64 inputsize,u64 outputsize,f64 *new_input);
}CML_CKNNRegression;



CML_CKNNRegression *CML_CKNNRegression_init(CML_Hyperparams hyperparams); 
void CML_CKNNRegression_fini(CML_CKNNRegression *knn);








typedef struct CML_CLogisticRegression
{
    CML_Hyperparams hyperparams;
    CML_ACVec *acvec;
    CML_Vec weight_vec;
    void (*fit)(void *self,f64 *input_X,u64 inputsize,f64 *output_Y,u64 outputsize);
    f64 (*predict)(void *self,f64 *input_X,u64 inputsize);
    void (*print)(void *self);
}CML_CLogisticRegression;




CML_CLogisticRegression *CML_CLogisticRegression_init(CML_Hyperparams hyperparams); 

void CML_CLogisticRegression_fini(CML_CLogisticRegression *linear);




typedef struct CML_CKNNClassifier
{
    CML_Hyperparams hyperparams;
    CML_ACVec *acvec;
    i64 (*predict)(void *self,f64 *input,u64 inputsize,u64 outputsize,u64 classes,f64 *new_input);
}CML_CKNNClassifier;



CML_CKNNClassifier *CML_CKNNClassifier_init(CML_Hyperparams hyperparams); 
void CML_CKNNClassifier_fini(CML_CKNNClassifier *knn);





#endif

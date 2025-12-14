#include "../include/ml.h"





void cml_ml_linear_regression_fit(void *self,f64 *input_X,u64 inputsize,f64 *output_Y,u64 outputsize)
{
    CML_Vec input_vecs[outputsize];
    CML_Vec weight_vec;
    CML_Vec output_vec;
    CML_Vec update_vec;

    CML_CLinearRegression *self_new = (CML_CLinearRegression *)self;


    if(CML_CHECK_NULL(input_X) || CML_CHECK_NULL(output_Y))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    for(u64 i = 0; i < outputsize; i++)
    {
        input_vecs[i] = self_new->acvec->alloc(inputsize + 1);
        self_new->acvec->set(&(input_vecs[i]),input_X + (i * inputsize) - 1);
        self_new->acvec->set_element(&(input_vecs[i]),0,1);
    }

    weight_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->randomize(&weight_vec,0,10);

    update_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->zero(&update_vec);

    output_vec = self_new->acvec->alloc(outputsize);
    self_new->acvec->set(&output_vec,output_Y);

    for(u64 k = 0; k < self_new->hyperparams.training_count; k++)
    {
        f64 sum = 0.0f;
        for(u64 i = 0; i < inputsize + 1; i++)
        {
            sum = 0;
            for(u64 j = 0; j < outputsize; j++)
            {
                f64 ytrue = self_new->acvec->get_element(&output_vec,j);
                f64 yhat = self_new->acvec->dot(&weight_vec,&(input_vecs[j]));
                f64 x = self_new->acvec->get_element(&(input_vecs[j]),i);

                sum += (yhat - ytrue) * x;
            }

            sum *= self_new->hyperparams.learning_rate;
            sum /= outputsize;
            self_new->acvec->set_element(&update_vec,i,sum);
        }

        self_new->acvec->sub(&weight_vec,&update_vec);
    }

    self_new->weight_vec = weight_vec;

    CML_RETURN_DEFER_NO_ERRNO(free_output_vec);

free_output_vec:
    self_new->acvec->free(&output_vec);
    CML_RETURN_DEFER_NO_ERRNO(free_update_vec);

free_update_vec:
    self_new->acvec->free(&update_vec);
    CML_RETURN_DEFER_NO_ERRNO(free_input_vecs);

free_input_vecs:
    for(u64 i = 0; i < outputsize; i++)
    {
        self_new->acvec->free(&(input_vecs[i]));
    }

null_whatever:
    return;
}




f64 cml_ml_linear_regression_predict(void *self,f64 *input_X,u64 inputsize)
{
    if(CML_CHECK_NULL(self) || CML_CHECK_NULL(input_X))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    CML_CLinearRegression *self_new = (CML_CLinearRegression *)self;
    
    CML_Vec input_vec;
    input_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->set_element(&input_vec,0,1);

    for(u64 i = 0; i < inputsize; i++)
    {
        self_new->acvec->set_element(&(input_vec),i + 1,input_X[i]);
    }

    f64 predicted = self_new->acvec->dot(&(self_new->weight_vec),&input_vec);
    self_new->acvec->free(&(input_vec));

    return predicted;

null_whatever:
    return -1;
}




void cml_ml_linear_regression_print(void *self)
{
    if(CML_CHECK_NULL(self))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_self);
    }

    CML_CLinearRegression *self_new = (CML_CLinearRegression *)self;
    self_new->acvec->print(&(self_new->weight_vec));

null_self:
    return;
}




CML_CLinearRegression *CML_CLinearRegression_init(CML_Hyperparams hyperparams)
{
    CML_CLinearRegression *linear = CML_CALLOC(1,sizeof(CML_CLinearRegression));
    if(CML_CHECK_NULL(linear))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_linear);
    }

    

    linear->hyperparams.learning_rate = hyperparams.learning_rate;
    linear->hyperparams.training_count = hyperparams.training_count;
    linear->acvec = CML_ACVec_init();

    if(CML_CHECK_NULL(linear->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec_class);
    }

    linear->fit     = cml_ml_linear_regression_fit;
    linear->predict = cml_ml_linear_regression_predict;
    linear->print   = cml_ml_linear_regression_print;

null_vec_class:
null_linear:
    return linear;
}


void CML_CLinearRegression_fini(CML_CLinearRegression *linear)
{
    if(CML_CHECK_NULL(linear) || CML_CHECK_NULL(linear->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    linear->acvec->free(&(linear->weight_vec));

    if(linear->acvec)
    {
        CML_ACVec_fini(linear->acvec);
    }

    CML_FREE(linear);

null_whatever:
    return;
}













void cml_ml_logistic_regression_fit(void *self,f64 *input_X,u64 inputsize,f64 *output_Y,u64 outputsize)
{
    CML_Vec input_vecs[outputsize];
    CML_Vec weight_vec;
    CML_Vec output_vec;
    CML_Vec update_vec;

    CML_CLogisticRegression *self_new = (CML_CLogisticRegression *)self;


    if(CML_CHECK_NULL(input_X) || CML_CHECK_NULL(output_Y))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    for(u64 i = 0; i < outputsize; i++)
    {
        input_vecs[i] = self_new->acvec->alloc(inputsize + 1);
        self_new->acvec->set(&(input_vecs[i]),input_X + (i * inputsize) - 1);
        self_new->acvec->set_element(&(input_vecs[i]),0,1);
    }

    weight_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->randomize(&weight_vec,0,10);

    update_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->zero(&update_vec);

    output_vec = self_new->acvec->alloc(outputsize);
    self_new->acvec->set(&output_vec,output_Y);

    for(u64 k = 0; k < self_new->hyperparams.training_count; k++)
    {
        f64 sum = 0.0f;
        for(u64 i = 0; i < inputsize + 1; i++)
        {
            sum = 0;
            for(u64 j = 0; j < outputsize; j++)
            {
                f64 ytrue = self_new->acvec->get_element(&output_vec,j);
                f64 yhat = cml_sigmoid(self_new->acvec->dot(&weight_vec,&(input_vecs[j])));
                f64 x = self_new->acvec->get_element(&(input_vecs[j]),i);

                sum += (yhat - ytrue) * x;
            }

            sum *= self_new->hyperparams.learning_rate;
            sum /= outputsize;
            self_new->acvec->set_element(&update_vec,i,sum);
        }

        self_new->acvec->sub(&weight_vec,&update_vec);
    }

    self_new->weight_vec = weight_vec;

    CML_RETURN_DEFER_NO_ERRNO(free_output_vec);

free_output_vec:
    self_new->acvec->free(&output_vec);
    CML_RETURN_DEFER_NO_ERRNO(free_update_vec);

free_update_vec:
    self_new->acvec->free(&update_vec);
    CML_RETURN_DEFER_NO_ERRNO(free_input_vecs);

free_input_vecs:
    for(u64 i = 0; i < outputsize; i++)
    {
        self_new->acvec->free(&(input_vecs[i]));
    }

null_whatever:
    return;
}




f64 cml_ml_logistic_regression_predict(void *self,f64 *input_X,u64 inputsize)
{
    if(CML_CHECK_NULL(self) || CML_CHECK_NULL(input_X))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    CML_CLogisticRegression *self_new = (CML_CLogisticRegression *)self;
    
    CML_Vec input_vec;
    input_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->set_element(&input_vec,0,1);

    for(u64 i = 0; i < inputsize; i++)
    {
        self_new->acvec->set_element(&(input_vec),i + 1,input_X[i]);
    }

    f64 predicted = cml_sigmoid(self_new->acvec->dot(&(self_new->weight_vec),&input_vec));
    self_new->acvec->free(&(input_vec));

    return predicted;

null_whatever:
    return -1;
}


void cml_ml_logistic_regression_print(void *self)
{
    if(CML_CHECK_NULL(self))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_self);
    }

    CML_CLogisticRegression *self_new = (CML_CLogisticRegression *)self;
    self_new->acvec->print(&(self_new->weight_vec));

null_self:
    return;
}



CML_CLogisticRegression *CML_CLogisticRegression_init(CML_Hyperparams hyperparams)
{
    CML_CLogisticRegression *logistic = CML_CALLOC(1,sizeof(CML_CLogisticRegression));
    if(CML_CHECK_NULL(logistic))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_linear);
    }


    logistic->hyperparams.learning_rate = hyperparams.learning_rate;
    logistic->hyperparams.training_count = hyperparams.training_count;
    logistic->acvec = CML_ACVec_init();

    if(CML_CHECK_NULL(logistic->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec_class);
    }

    logistic->fit     = cml_ml_logistic_regression_fit;
    logistic->predict = cml_ml_logistic_regression_predict;
    logistic->print   = cml_ml_logistic_regression_print;

null_vec_class:
null_linear:
    return logistic;
}


void CML_CLogisticRegression_fini(CML_CLogisticRegression *logistic)
{
    if(CML_CHECK_NULL(logistic) || CML_CHECK_NULL(logistic->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    logistic->acvec->free(&(logistic->weight_vec));

    if(logistic->acvec)
    {
        CML_ACVec_fini(logistic->acvec);
    }

    CML_FREE(logistic);

null_whatever:
    return;
}











void cml_ml_lasso_regression_fit(void *self,f64 *input_X,u64 inputsize,f64 *output_Y,u64 outputsize)
{
    CML_Vec input_vecs[outputsize];
    CML_Vec weight_vec;
    CML_Vec output_vec;
    CML_Vec update_vec;

    CML_CLassoRegression *self_new = (CML_CLassoRegression *)self;


    if(CML_CHECK_NULL(input_X) || CML_CHECK_NULL(output_Y))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    for(u64 i = 0; i < outputsize; i++)
    {
        input_vecs[i] = self_new->acvec->alloc(inputsize + 1);
        self_new->acvec->set(&(input_vecs[i]),input_X + (i * inputsize) - 1);
        self_new->acvec->set_element(&(input_vecs[i]),0,1);
    }

    weight_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->randomize(&weight_vec,0,10);

    update_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->zero(&update_vec);

    output_vec = self_new->acvec->alloc(outputsize);
    self_new->acvec->set(&output_vec,output_Y);

    for(u64 k = 0; k < self_new->hyperparams.training_count; k++)
    {
        f64 sum = 0.0f;
        for(u64 i = 0; i < inputsize + 1; i++)
        {
            sum = 0;
            for(u64 j = 0; j < outputsize; j++)
            {
                f64 ytrue = self_new->acvec->get_element(&output_vec,j);
                f64 yhat = self_new->acvec->dot(&weight_vec,&(input_vecs[j]));
                f64 x = self_new->acvec->get_element(&(input_vecs[j]),i);
                f64 w = self_new->acvec->get_element(&(weight_vec),i);

                if(w < 0)
                {
                    sum += (yhat - ytrue) * x - self_new->hyperparams.lambda;
                }
                else
                {
                    sum += (yhat - ytrue) * x + self_new->hyperparams.lambda;
                }
            }

            sum *= self_new->hyperparams.learning_rate;
            sum /= outputsize;
            self_new->acvec->set_element(&update_vec,i,sum);
        }

        self_new->acvec->sub(&weight_vec,&update_vec);
    }

    self_new->weight_vec = weight_vec;

    CML_RETURN_DEFER_NO_ERRNO(free_output_vec);

free_output_vec:
    self_new->acvec->free(&output_vec);
    CML_RETURN_DEFER_NO_ERRNO(free_update_vec);

free_update_vec:
    self_new->acvec->free(&update_vec);
    CML_RETURN_DEFER_NO_ERRNO(free_input_vecs);

free_input_vecs:
    for(u64 i = 0; i < outputsize; i++)
    {
        self_new->acvec->free(&(input_vecs[i]));
    }

null_whatever:
    return;
}




f64 cml_ml_lasso_regression_predict(void *self,f64 *input_X,u64 inputsize)
{
    if(CML_CHECK_NULL(self) || CML_CHECK_NULL(input_X))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    CML_CLassoRegression *self_new = (CML_CLassoRegression *)self;
    
    CML_Vec input_vec;
    input_vec = self_new->acvec->alloc(inputsize + 1);
    self_new->acvec->set_element(&input_vec,0,1);

    for(u64 i = 0; i < inputsize; i++)
    {
        self_new->acvec->set_element(&(input_vec),i + 1,input_X[i]);
    }

    f64 predicted = self_new->acvec->dot(&(self_new->weight_vec),&input_vec);
    self_new->acvec->free(&(input_vec));

    return predicted;

null_whatever:
    return -1;
}




void cml_ml_lasso_regression_print(void *self)
{
    if(CML_CHECK_NULL(self))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_self);
    }

    CML_CLassoRegression *self_new = (CML_CLassoRegression *)self;
    self_new->acvec->print(&(self_new->weight_vec));

null_self:
    return;
}








CML_CLassoRegression *CML_CLassoRegression_init(CML_Hyperparams hyperparams)
{
    CML_CLassoRegression *lasso = CML_CALLOC(1,sizeof(CML_CLassoRegression));
    if(CML_CHECK_NULL(lasso))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_lasso);
    }

    

    lasso->hyperparams.learning_rate  = hyperparams.learning_rate;
    lasso->hyperparams.training_count = hyperparams.training_count;
    lasso->hyperparams.lambda         = hyperparams.lambda;
    lasso->acvec = CML_ACVec_init();

    if(CML_CHECK_NULL(lasso->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec_class);
    }

    lasso->fit     = cml_ml_lasso_regression_fit;
    lasso->predict = cml_ml_lasso_regression_predict;
    lasso->print   = cml_ml_lasso_regression_print;

null_vec_class:
null_lasso:
    return lasso;
}



void CML_CLassoRegression_fini(CML_CLassoRegression *lasso)
{
    if(CML_CHECK_NULL(lasso) || CML_CHECK_NULL(lasso->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    lasso->acvec->free(&(lasso->weight_vec));

    if(lasso->acvec)
    {
        CML_ACVec_fini(lasso->acvec);
    }

    CML_FREE(lasso);

null_whatever:
    return;
}




#define CML_ML_KNN_CLASSIFICATION_PRINT_DEBUG() for(u64 i = 0; i < outputsize; i++)\
    {\
        CML_PRINTF("%lf  -->",points[i].distance);\
        CML_PRINTF("%lf  ",points[i].Y_output);\
        self_new->acvec->print(&(points[i].X_inputs));\
    }\
\
    point.Y_output = output_class;\
    CML_PRINTF("%lf  ",point.Y_output);\
    self_new->acvec->print(&(point.X_inputs));\
    CML_RETURN_DEFER_NO_ERRNO(free_frequency)







typedef struct CML_PointData
{
    CML_Vec X_inputs;
    f64 Y_output;
    f64 distance;
}CML_PointData;

int cml_ml_knn_compare_input(const void *a,const void *b)
{
    CML_PointData *pointA = (CML_PointData *)a;
    CML_PointData *pointB = (CML_PointData *)b;

    if(pointA->distance < pointB->distance)return -1;
    if(pointA->distance > pointB->distance)return 1;
    return 0;
}


i64 cml_ml_knn_classifier_predict(void *self,f64 *input,u64 inputsize,u64 outputsize,u64 classes,f64 *new_input)
{
    CML_PointData points[outputsize];
    CML_PointData point;
    u64 eps = 0;
    u64 *frequency = NULL;
    u64 max_freq = 0;
    i64 output_class = -1;

    if(CML_CHECK_NULL(self) || CML_CHECK_NULL(input) || CML_CHECK_NULL(new_input))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_arrays);
    }

    CML_CKNNClassifier *self_new = (CML_CKNNClassifier *)self;
   

    point.X_inputs = self_new->acvec->alloc(inputsize);
    self_new->acvec->set(&(point.X_inputs),new_input);
    point.Y_output = new_input[inputsize];


    eps = 0;
    for(u64 i = 0; i < outputsize; i++)
    { 
        points[i].X_inputs = self_new->acvec->alloc(inputsize);
        self_new->acvec->set(&(points[i].X_inputs),input + (i * inputsize) + eps);
        points[i].Y_output = input[((i + 1) * inputsize) + eps++];
        points[i].distance = self_new->acvec->euclidean_distance(&(points[i].X_inputs),&(point.X_inputs));
    }

    CML_QSORT(points,outputsize,sizeof(CML_PointData),cml_ml_knn_compare_input);


    frequency = (u64 *)CML_CALLOC(classes,sizeof(u64));

    for(u64 i = 0; i < self_new->hyperparams.neighbors; i++)
    {
        int j = (int)points[i].Y_output;
        frequency[j]++;
    }


   

    for(u64 i = 0; i < classes; i++)
    {
        if(frequency[i] > max_freq)
        {
            max_freq = frequency[i];
            output_class = i;
        }
    }
    
    CML_RETURN_DEFER_NO_ERRNO(free_frequency);
    //CML_ML_KNN_CLASSIFICATION_PRINT_DEBUG();

free_frequency:
    CML_FREE(frequency);
    CML_RETURN_DEFER_NO_ERRNO(free_points);
free_points:
    for(u64 i = 0; i < outputsize; i++)
    {
        self_new->acvec->free(&(points[i].X_inputs));
    }
    CML_RETURN_DEFER_NO_ERRNO(free_point);
free_point:
    self_new->acvec->free(&(point.X_inputs));
null_arrays:
    return output_class;
}

CML_CKNNClassifier *CML_CKNNClassifier_init(CML_Hyperparams hyperparams)
{
    CML_CKNNClassifier *knn = CML_CALLOC(1,sizeof(CML_CKNNClassifier));
    if(CML_CHECK_NULL(knn))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_knn);
    }


    knn->hyperparams.neighbors = hyperparams.neighbors;
    knn->acvec = CML_ACVec_init();
    knn->predict = cml_ml_knn_classifier_predict;

    if(CML_CHECK_NULL(knn->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec_class);
    }

    

null_vec_class:
null_knn:
    return knn;
} 



void CML_CKNNClassifier_fini(CML_CKNNClassifier *knn)
{
    if(CML_CHECK_NULL(knn) || CML_CHECK_NULL(knn->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    

    if(knn->acvec)
    {
        CML_ACVec_fini(knn->acvec);
    }

    CML_FREE(knn);

null_whatever:
    return;
}






#define CML_ML_KNN_REGRESSION_PRINT_DEBUG() for(u64 i = 0; i < outputsize; i++)\
{\
    CML_PRINTF("%lf  -->",points[i].distance); \
    CML_PRINTF("%lf  ",points[i].Y_output); \
    self_new->acvec->print(&(points[i].X_inputs)); \
}\
\
point.Y_output = mean; \
CML_PRINTF("%lf  ",point.Y_output);\
self_new->acvec->print(&(point.X_inputs));\
CML_RETURN_DEFER_NO_ERRNO(free_points)



f64 cml_ml_knn_regression_predict(void *self,f64 *input,u64 inputsize,u64 outputsize,f64 *new_input)
{
    CML_PointData points[outputsize];
    CML_PointData point;
    u64 eps = 0;
    f64 mean = 0;

    if(CML_CHECK_NULL(self) || CML_CHECK_NULL(input) || CML_CHECK_NULL(new_input))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_arrays);
    }

    CML_CKNNRegression *self_new = (CML_CKNNRegression *)self;
   

    point.X_inputs = self_new->acvec->alloc(inputsize);
    self_new->acvec->set(&(point.X_inputs),new_input);
    point.Y_output = new_input[inputsize];


    eps = 0;
    for(u64 i = 0; i < outputsize; i++)
    { 
        points[i].X_inputs = self_new->acvec->alloc(inputsize);
        self_new->acvec->set(&(points[i].X_inputs),input + (i * inputsize) + eps);
        points[i].Y_output = input[((i + 1) * inputsize) + eps++];
        points[i].distance = self_new->acvec->euclidean_distance(&(points[i].X_inputs),&(point.X_inputs));
    }

    CML_QSORT(points,outputsize,sizeof(CML_PointData),cml_ml_knn_compare_input);


    mean = 0;
    for(u64 i = 0; i < self_new->hyperparams.neighbors; i++)
    {
        mean += points[i].Y_output;
    }

    mean /= self_new->hyperparams.neighbors;

    
    CML_RETURN_DEFER_NO_ERRNO(free_points);
    //CML_ML_KNN_REGRESSION_PRINT_DEBUG();



free_points:
    for(u64 i = 0; i < outputsize; i++)
    {
        self_new->acvec->free(&(points[i].X_inputs));
    }
    CML_RETURN_DEFER_NO_ERRNO(free_point);
free_point:
    self_new->acvec->free(&(point.X_inputs));
null_arrays:
    return mean;
}



CML_CKNNRegression *CML_CKNNRegression_init(CML_Hyperparams hyperparams)
{
    CML_CKNNRegression *knn = CML_CALLOC(1,sizeof(CML_CKNNRegression));
    if(CML_CHECK_NULL(knn))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_knn);
    }


    knn->hyperparams.neighbors = hyperparams.neighbors;
    knn->acvec = CML_ACVec_init();
    knn->predict = cml_ml_knn_regression_predict;

    if(CML_CHECK_NULL(knn->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec_class);
    }

    

null_vec_class:
null_knn:
    return knn;
} 



void CML_CKNNRegression_fini(CML_CKNNRegression *knn)
{
    if(CML_CHECK_NULL(knn) || CML_CHECK_NULL(knn->acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_whatever);
    }

    

    if(knn->acvec)
    {
        CML_ACVec_fini(knn->acvec);
    }

    CML_FREE(knn);

null_whatever:
    return;
}


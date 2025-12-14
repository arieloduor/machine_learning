#include "../include/math.h"


f64 cml_rand_float(i64 min,i64 max)
{
    return (CML_RAND() / (f64)RAND_MAX) * (f64)(max - min);
}


f64 cml_sigmoid(f64 x)
{
    return (1 / (1 + (exp(-x))));
}

f64 cml_sigmoid_derivative(f64 x)
{
    return (cml_sigmoid(x) * (1 - cml_sigmoid(x)));
}

#ifndef CML_MATH_H
#define CML_MATH_H


#include "utils.h"
#include <math.h>

#ifndef CML_SQRT
#define CML_SQRT sqrt
#endif

#ifndef CML_POW
#define CML_POW pow
#endif

#ifndef CML_ACOS
#define CML_ACOS acos
#endif

#ifndef CML_RAND
#define CML_RAND rand
#endif

#ifndef CML_SRAND
#define CML_SRAND srand
#endif


f64 cml_rand_float(i64 min,i64 max);
f64 cml_sigmoid(f64 x);
f64 cml_sigmoid_derivative(f64 x);



#endif

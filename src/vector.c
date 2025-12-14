#include "../include/vector.h"
#include "../include/math.h"



static CML_Vec cml_vec_alloc(u32 dimension);
static void cml_vec_free(CML_Vec *vec);
static f64 cml_vec_get_element(const CML_Vec *vec,u32 index);
static void cml_vec_set_element(const CML_Vec *vec,u32 index,f64 value);
static void cml_vec_print(const CML_Vec *vec);
static void cml_vec_fill(const CML_Vec *vec,f64 value);
static void cml_vec_zero(const CML_Vec *vec);
static void cml_vec_randomize(const CML_Vec *vec,i64 min,i64 max);
static void cml_vec_set_elements(const CML_Vec *vec,f64 *array);
static void cml_vec_add(const CML_Vec *dstvec,const CML_Vec *srcvec);
static void cml_vec_sub(const CML_Vec *dstvec,const CML_Vec *srcvec);
static void cml_vec_mul(const CML_Vec *vec,f64 value);
static void cml_vec_div(const CML_Vec *vec,f64 value);
static f64 cml_vec_dot(const CML_Vec *vec1,const CML_Vec *vec2);
static f64 cml_vec_length(const CML_Vec *vec);
static f64 cml_vec_euclidean_distance(const CML_Vec *vec1,const CML_Vec *vec2);
static f64 cml_vec_angle(const CML_Vec *vec1,const CML_Vec *vec2);
static bool cml_vec_equal(const CML_Vec *vec1,const CML_Vec *vec2);




static CML_Vec cml_vec_alloc(u32 dimension)
{
    CML_Vec vec = {
        .ret.ret       = 0,
        .ret._errno    = 0,
        .dimension = dimension,
        .array     = NULL,
    };

    vec.array = (f64 *)CML_CALLOC(vec.dimension,sizeof(f64));
    if(CML_CHECK_NULL(vec.array))
    {
        CML_RETURN_DEFER_NO_ERRNO(failed_calloc);
    }

    CML_RETURN_DEFER_NO_ERRNO(success_calloc);

failed_calloc:
    vec.ret.ret = -1;
    vec.ret._errno = errno;
success_calloc:
    return vec;
}



static void cml_vec_free(CML_Vec *vec)
{
    if(CML_CHECK_NULL(vec))
        return;

    vec->dimension = vec->ret.ret = vec->ret._errno = 0;
    return CML_FREE(vec->array);
}

static f64 cml_vec_get_element(const CML_Vec *vec,u32 index)
{
    if(CML_CHECK_NULL(vec) || index > vec->dimension)
        return -1;
    
    return vec->array[index];
}


static void cml_vec_set_element(const CML_Vec *vec,u32 index,f64 value)
{
    if(CML_CHECK_NULL(vec) || index > vec->dimension)
        return;
    
    vec->array[index] = value;
}



static void cml_vec_print(const CML_Vec *vec)
{
    if(CML_CHECK_NULL(vec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    CML_PRINTF("[ ");
    for(u32 i = 0; i < vec->dimension; i++)
    {
        CML_PRINTF("%lf ",vec->array[i]);
    }
    CML_PRINTF("  ]\n");
    CML_RETURN_DEFER_NO_ERRNO(success_print);

success_print:
    return;
null_vec:
    return;
}


static void cml_vec_fill(const CML_Vec *vec,f64 value)
{
    if(CML_CHECK_NULL(vec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    for(u32 i = 0; i < vec->dimension; i++)
    {
        vec->array[i] = value;
    }

    CML_RETURN_DEFER_NO_ERRNO(success_fill);

success_fill:
    return;
null_vec:
    return;
}




static void cml_vec_zero(const CML_Vec *vec)
{
    return cml_vec_fill(vec,0);
}



static void cml_vec_randomize(const CML_Vec *vec,i64 min,i64 max)
{
    if(CML_CHECK_NULL(vec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    CML_SRAND(CML_TIME(NULL));

    for(u32 i = 0; i < vec->dimension; i++)
    {
        vec->array[i] = cml_rand_float(min,max);
    }

    CML_RETURN_DEFER_NO_ERRNO(success_fill);

success_fill:
    return;
null_vec:
    return;
}



static void cml_vec_set_elements(const CML_Vec *vec,f64 *array)
{
    if(CML_CHECK_NULL(vec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    if(CML_CHECK_NULL(array))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_array);
    }

    for(u32 i = 0; i < vec->dimension; i++)
    {
        vec->array[i] = array[i];
    }

    CML_RETURN_DEFER_NO_ERRNO(success_fill);

success_fill:
    return;
null_array:
    return;
null_vec:
    return;
}





static void cml_vec_add(const CML_Vec *dstvec,const CML_Vec *srcvec)
{
    if(CML_CHECK_NULL(dstvec) || CML_CHECK_NULL(srcvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    if(CML_CHECK_NOT_EQUAL(dstvec->dimension,srcvec->dimension))
    {
        CML_RETURN_DEFER_NO_ERRNO(unmatching_dimensions);
    }

    for(u32 i = 0; i < dstvec->dimension; i++)
    {
        dstvec->array[i] += srcvec->array[i];
    }

    CML_RETURN_DEFER_NO_ERRNO(success_add);

success_add:
    return;
unmatching_dimensions:
    return;
null_vec:
    return;
}



static void cml_vec_sub(const CML_Vec *dstvec,const CML_Vec *srcvec)
{
    if(CML_CHECK_NULL(dstvec) || CML_CHECK_NULL(srcvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    if(CML_CHECK_NOT_EQUAL(dstvec->dimension,srcvec->dimension))
    {
        CML_RETURN_DEFER_NO_ERRNO(unmatching_dimensions);
    }

    for(u32 i = 0; i < dstvec->dimension; i++)
    {
        dstvec->array[i] -= srcvec->array[i];
    }

    CML_RETURN_DEFER_NO_ERRNO(success_ok);

success_ok:
    return;
unmatching_dimensions:
    return;
null_vec:
    return;
}



static void cml_vec_mul(const CML_Vec *vec,f64 value)
{
    if(CML_CHECK_NULL(vec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    for(u32 i = 0; i < vec->dimension; i++)
    {
        vec->array[i] *= value;
    }

    CML_RETURN_DEFER_NO_ERRNO(success_mul);

success_mul:
    return;
null_vec:
    return;
}



static void cml_vec_div(const CML_Vec *vec,f64 value)
{
    if(CML_CHECK_NULL(vec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    if(CML_CHECK_EQUAL(value,0))
    {
        CML_RETURN_DEFER_NO_ERRNO(zero_division);
    }

    for(u32 i = 0; i < vec->dimension; i++)
    {
        vec->array[i] /= value;
    }

    CML_RETURN_DEFER_NO_ERRNO(success_div);

success_div:
    return;
zero_division:
    return;
null_vec:
    return;
}



static f64 cml_vec_dot(const CML_Vec *vec1,const CML_Vec *vec2)
{
    f64 result = 0.0;

    if(CML_CHECK_NULL(vec1) || CML_CHECK_NULL(vec2))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    if(CML_CHECK_NOT_EQUAL(vec1->dimension,vec2->dimension))
    {
        CML_RETURN_DEFER_NO_ERRNO(unmatched_dimensions);
    }

    for(u32 i = 0; i < vec1->dimension; i++)
    {
        result += vec1->array[i] * vec2->array[i];
    }

    CML_RETURN_DEFER_NO_ERRNO(dot_ok);

unmatched_dimensions:
null_vec:
    result = -1.0;
dot_ok:
    return result;
}


static f64 cml_vec_length(const CML_Vec *vec)
{
    f64 length = 0.0;
    length = cml_vec_dot(vec,vec);
    if(CML_CHECK_EQUAL(length,(double)-1.0))
    {
        CML_RETURN_DEFER_NO_ERRNO(failed_length);
    }

    length = CML_SQRT(length);
    CML_RETURN_DEFER_NO_ERRNO(length_ok);

failed_length:
length_ok:
    return length; 
}


static f64 cml_vec_euclidean_distance(const CML_Vec *vec1,const CML_Vec *vec2)
{
    f64 result = 0.0;

    if(CML_CHECK_NULL(vec1) || CML_CHECK_NULL(vec2))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    if(CML_CHECK_NOT_EQUAL(vec1->dimension,vec2->dimension))
    {
        CML_RETURN_DEFER_NO_ERRNO(unmatched_dimensions);
    }

    for(u32 i = 0; i < vec1->dimension; i++)
    {
        result += CML_POW(vec1->array[i] - vec2->array[i],2);
    }

    CML_RETURN_DEFER_NO_ERRNO(dist_ok);

unmatched_dimensions:
null_vec:
    result = -1.0;
dist_ok:
    return CML_SQRT(result);
}


static void cml_vec_normalize(const CML_Vec *vec)
{
    f64 length = 0.0;

    if(CML_CHECK_NULL(vec))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    length = cml_vec_length(vec);
    return cml_vec_div(vec,length);

null_vec:
    return;
}



static f64 cml_vec_angle(const CML_Vec *vec1,const CML_Vec *vec2)
{
    f64 result1,result2;
    result1 = result2 = 0.0;
    result1 = cml_vec_dot(vec1,vec2);
    if(CML_CHECK_EQUAL(result1,(double)-1.0))
    {
        CML_RETURN_DEFER_NO_ERRNO(failed_angle);
    }

    result2 = cml_vec_length(vec1) * cml_vec_length(vec2);
    if(CML_CHECK_EQUAL(result2,0))
    {
        CML_RETURN_DEFER_NO_ERRNO(failed_angle);
    }

    CML_RETURN_DEFER_NO_ERRNO(success_angle);

success_angle:
    return CML_ACOS(result1 / result2);
failed_angle:
    return (double)-1.0;
}



static bool cml_vec_orthogonal(const CML_Vec *vec1,const CML_Vec *vec2)
{
    f64 result = cml_vec_dot(vec1,vec2);
    if(CML_CHECK_EQUAL(result,(double)0.0))
        return true;
    return false;
}


static bool cml_vec_equal(const CML_Vec *vec1,const CML_Vec *vec2)
{
    if(CML_CHECK_NULL(vec1) || CML_CHECK_NULL(vec2))
    {
        CML_RETURN_DEFER_NO_ERRNO(null_vec);
    }

    if(CML_CHECK_NOT_EQUAL(vec1->dimension,vec2->dimension))
    {
        CML_RETURN_DEFER_NO_ERRNO(unmatched_dimensions);
    }

    for(u32 i = 0; i < vec1->dimension; i++)
    {
        if(CML_CHECK_NOT_EQUAL(vec1->array[i],vec2->array[i]))
        {
            CML_RETURN_DEFER_NO_ERRNO(not_equal);
        }
    }

    CML_RETURN_DEFER_NO_ERRNO(equal);

equal:
    return true;
not_equal:
unmatched_dimensions:
null_vec:
    return false;
}



CML_ACVec *CML_ACVec_init(void)
{
    CML_ACVec *acvec = (CML_ACVec *)CML_CALLOC(1,sizeof(CML_ACVec)); 
    if(CML_CHECK_NULL(acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(acvec_null);
    }

    acvec->add                  = cml_vec_add;
    acvec->alloc                = cml_vec_alloc;
    acvec->angle                = cml_vec_angle;
    acvec->free                 = cml_vec_free;
    acvec->div                  = cml_vec_div;
    acvec->dot                  = cml_vec_dot;
    acvec->equal                = cml_vec_equal;
    acvec->euclidean_distance   = cml_vec_euclidean_distance;
    acvec->fill             = cml_vec_fill;
    acvec->get_element      = cml_vec_get_element;
    acvec->length           = cml_vec_length;
    acvec->mul              = cml_vec_mul;
    acvec->normalize        = cml_vec_normalize;
    acvec->orthogonal       = cml_vec_orthogonal;
    acvec->print            = cml_vec_print;
    acvec->randomize        = cml_vec_randomize;
    acvec->set              = cml_vec_set_elements;
    acvec->set_element      = cml_vec_set_element;
    acvec->sub              = cml_vec_sub;
    acvec->zero             = cml_vec_zero;

acvec_null:
    return acvec;
}


void CML_ACVec_fini(CML_ACVec *acvec)
{
    if(CML_CHECK_NULL(acvec))
    {
        CML_RETURN_DEFER_NO_ERRNO(acvec_null);
    }

    CML_FREE(acvec);
acvec_null:
    return;
}



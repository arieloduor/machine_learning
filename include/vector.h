#ifndef CML_VECTOR_H 
#define CML_VECTOR_H

#include "math.h"

typedef struct CML_Vec
{
    CML_Ret ret;
    u32 dimension;
    f64 *array;
}CML_Vec;



typedef struct CML_ACVec
{
    CML_Vec (*alloc)(u32 dimension);
    void   (*free)(CML_Vec *vec);
    f64 (*get_element)(const CML_Vec *vec,u32 index);
    void (*set_element)(const CML_Vec *vec,u32 index,f64 value);
    void (*print)(const CML_Vec *vec);
    void (*fill)(const CML_Vec *vec,f64 value);
    void (*zero)(const CML_Vec *vec);
    void (*randomize)(const CML_Vec *vec,i64 min,i64 max);
    void (*set)(const CML_Vec *vec,f64 *array);
    void (*add)(const CML_Vec *dstvec,const CML_Vec *srcvec);
    void (*sub)(const CML_Vec *dstvec,const CML_Vec *srcvec);
    void (*mul)(const CML_Vec *dstvec,f64 value);
    void (*div)(const CML_Vec *dstvec,f64 value);
    f64 (*dot)(const CML_Vec *vec1,const CML_Vec *vec2);
    f64 (*length)(const CML_Vec *vec);
    f64 (*euclidean_distance)(const CML_Vec *vec1,const CML_Vec *vec2);
    void (*normalize)(const CML_Vec *vec);
    f64 (*angle)(const CML_Vec *vec1,const CML_Vec *vec2);
    bool (*orthogonal)(const CML_Vec *vec1,const CML_Vec *vec2);
    bool (*equal)(const CML_Vec *vec1,const CML_Vec *vec2);
}CML_ACVec;


CML_ACVec *CML_ACVec_init(void);
void CML_ACVec_fini(CML_ACVec *acvec);



#endif

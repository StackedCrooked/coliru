#include <stdio.h>
 
int main()
{
    /* The pointer, the target of the pointer, or both may be const. */
 
    int i = 0;                                   /* A VARIABLE */
    int * ptr                            = &i;
    int const * ptr_to_const             = &i;
    int * const const_ptr                = &i;
    int const * const const_ptr_to_const = &i;
    const int* const c_p_t_c             = &i;   /* also valid */
 
    *ptr = 1;                   /* AOK: modifies the target       */
    ptr  = NULL;                /* AOK: modifies the pointer      */
    *ptr_to_const = 0;          /* NOK: cannot modify the target  */
    ptr_to_const  = NULL;       /* AOK: modifies the pointer      */
    *const_ptr = 0;             /* AOK: modifies the target       */
    const_ptr  = NULL;          /* NOK: cannot modify the pointer */
    *const_ptr_to_const = 0;    /* NOK: cannot modify the target  */
    const_ptr_to_const  = NULL; /* NOK: cannot modify the pointer */
 
    const int j = 0;                             /* A CONSTANT               */
    int const jj = 0;                            /* also valid               */
    int * j_ptr                            = &j; /* NOK: int* <== const int* */
    int const * j_ptr_to_const             = &j;
    int * const j_const_ptr                = &j; /* NOK: int* <== const int* */
    int const * const j_const_ptr_to_const = &j;
 
    *j_ptr = 1;                   /* AOK: modifies the target       */
    j_ptr  = NULL;                /* AOK: modifies the pointer      */
    *j_ptr_to_const = 0;          /* NOK: cannot modify the target  */
    j_ptr_to_const  = NULL;       /* AOK: modifies the pointer      */
    *j_const_ptr = 0;             /* AOK: modifies the target       */
    j_const_ptr  = NULL;          /* NOK: cannot modify the pointer */
    *j_const_ptr_to_const = 0;    /* NOK: cannot modify the target  */
    j_const_ptr_to_const  = NULL; /* NOK: cannot modify the pointer */
 
    return 0;
}
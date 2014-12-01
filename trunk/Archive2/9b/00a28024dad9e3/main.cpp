
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// return index of max element
int max_index( int* vec, int sz )
{
    int idx, max, i;
    
    if(!sz) return -1;
    
    idx = 0;
    max = vec[0];
    
    for(i=1; i<sz; ++i)
    {
        if( vec[i] > max )
        {
            max = vec[i];
            idx = i;
        }
    }
    
    return idx;
}

// return indexes of N top elements
void top( int* vec, int sz, int* out_vec, int N )
{
    int i, *tmp, idx;
    
    tmp = (int*) malloc( sz*sizeof(int) );
    memcpy( tmp, vec, sz*sizeof(int) );
    
    for(i=0; i<N; ++i )
    {
        idx = max_index(tmp,sz);
        out_vec[i]=idx;
        tmp[idx] = INT_MIN;
    }
    
    free(tmp);
}

int main()
{
    int iv1[] = { 55,66,77,88,2,4,5,6,99,123,22 };
    int iv2[6];
    int i,elem;
    
    top( iv1, sizeof(iv1)/sizeof(int), iv2, 6 );
    
    for( i=0; i<6; ++i)
    {
        elem=iv2[i];
        printf( "idx: %d val: %d\n", elem, iv1[elem] );
    }
}


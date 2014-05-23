#include <string.h>

typedef float float32;
typedef unsigned uint32;

void MyFunc( void * DataPtr, uint32 something ) {
    uint32 localval;
    localval = something;
    memcpy( DataPtr, &localval, sizeof(localval) );
}

#include <stdio.h>
#include <inttypes.h>

const char* SCN_SIZE_T()
{
    switch ( sizeof(size_t) )
    {
        case sizeof(uint16_t) : return "%" SCNu16 "u";
        case sizeof(uint32_t) : return "%" SCNu32 "u" ;
        case sizeof(uint64_t) : return "%" SCNu64 "u" ;
        default: return "%u" ;
    }
}

int main()
{
    size_t numOfElements;
    scanf( SCN_SIZE_T(), &numOfElements ) ;
    printf( "numOfElements: %" PRIuMAX "\n", (uintmax_t)numOfElements ) ;
}

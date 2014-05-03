#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void packarray(unsigned char *buff, int len)
{ 
    unsigned char *packed;
    unsigned char byte;
    assert(len >= 2);  /* len must be at least 2 bytes */
    assert((len & 1) != 1);   /* len must be an even number */
    for (packed = buff; len; len-=2) {
        byte= *buff++;
        *packed++ = (byte << 4) | *buff++;
    }
}

int main() 
{
    struct timeval start, end, result;
    const unsigned maxsize = 30000000;
    unsigned char *buff = (unsigned char *)malloc(maxsize);
    unsigned i, tries;
    for (tries=10; tries; --tries) {
        if (buff != NULL) {
        for (i=0; i < maxsize; ++i)
     	    buff[i] = i&0xf;
        }
        gettimeofday(&start,0);
        packarray(buff, maxsize);
        gettimeofday(&end, 0);
        timersub(&end, &start, &result);
        printf("Time = %ld us\n", result.tv_usec);
    }
    free(buff);
}

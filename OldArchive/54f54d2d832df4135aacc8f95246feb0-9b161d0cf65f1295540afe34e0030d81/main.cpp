


#ifndef N
#define N 0
#define M 0
#endif 


__LINE__ N
__LINE__ M


#undef M
#define M N + 1


__LINE__ N
__LINE__ M


#undef N
#define N M + 1


__LINE__ N
__LINE__ M


#include "main.cpp"

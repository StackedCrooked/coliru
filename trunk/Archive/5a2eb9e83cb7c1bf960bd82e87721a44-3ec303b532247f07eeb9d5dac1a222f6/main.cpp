#define ARG_N(_1,_2,_3,_4,_5,_6,N,...) N
#define NARG_(...) ARG_N(__VA_ARGS__)
#define NARG(...) NARG_(__VA_ARGS__,6,5,4,3,2,1,0)


NARG(a)
NARG(a, b)
NARG(a, b, c)
NARG(a, b, c, d)
NARG(a, b, c, d, e)
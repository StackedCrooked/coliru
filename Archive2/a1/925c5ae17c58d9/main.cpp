#define FOO_CAT(n) int foo##n;
#define FOO FOO_CAT(__COUNTER__)

FOO

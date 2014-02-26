#define CAT(a, b) a##b

#define FOO_CAT(n) CAT(int foo, n);
#define FOO FOO_CAT(__COUNTER__)

FOO

#define f(a)    f(2 * (a))
#define g       f
#define t(a)    a

t(t(g)(0) + t)(1);  // results in f(2 * (0)) + t(1);
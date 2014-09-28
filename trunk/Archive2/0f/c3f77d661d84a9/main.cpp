#define REPEAT_I_0(X)
#define REPEAT_I_1(X) X(1)
#define REPEAT_I_2(X) REPEAT_I_1(X) X(2)
#define REPEAT_I_3(X) REPEAT_I_2(X) X(3)
#define REPEAT_I_4(X) REPEAT_I_3(X) X(4)
#define REPEAT_I_5(X) REPEAT_I_4(X) X(5)

#define REPEAT_I(X, N) REPEAT_I_ ## N (X)


#define REPEAT_JC_0(X)
#define REPEAT_JC_1(X) X ## 1
#define REPEAT_JC_2(X) REPEAT_JC_1(X), X ## 2
#define REPEAT_JC_3(X) REPEAT_JC_2(X), X ## 3
#define REPEAT_JC_4(X) REPEAT_JC_3(X), X ## 4
#define REPEAT_JC_5(X) REPEAT_JC_4(X), X ## 5

#define REPEAT_JC(X, N) REPEAT_JC_ ## N (X)


#define FUNC(N) void foo( REPEAT_JC(int a, N) ) {}

REPEAT_I(FUNC, 4)
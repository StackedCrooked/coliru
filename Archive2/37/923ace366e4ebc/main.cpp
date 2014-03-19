#define SAY_HELLO(X) Hello, X!

#define FIRST(x) SAY_##x
#define DELAY_SECOND(x) (x
#define SECOND(x) DELAY_SECOND(x)
#define THIRD(x) )

#define MACRO(PARAM0, PARAM1, PARAM2) PARAM0 PARAM1 PARAM2

MACRO(FIRST(HELLO), SECOND(World), THIRD(dummy))

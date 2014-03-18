#define SAY_HELLO(X) Hello, X!

#define FIRST(x) SAY_##x
#define SECOND(x) (x
#define THIRD(x) )

#define MACRO(PARAM0, PARAM1, PARAM2) PARAM0 PARAM1 PARAM2

MACRO(FIRST(HELLO), SECOND(World), THIRD(dummy))

#if defined(__clang__)
#define PRAGMA(x) _Pragma ("clang "x)
#elif defined (__GNUC__)
#define PRAGMA(x) _Pragma ("GCC "x)
#endif

PRAGMA("diagnostic push")
PRAGMA("diagnostic ignored \"-Wwhatever\"")
// some code here
PRAGMA("diagnostic pop")
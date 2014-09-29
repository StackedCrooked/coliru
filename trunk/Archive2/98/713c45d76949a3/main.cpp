#define STRINGIZE_PRAGMA(x) _Pragma(#x)

#if defined(__clang__)
#define PRAGMA(x) STRINGIZE_PRAGMA (clang x)
#elif defined (__GNUC__)
#define PRAGMA(x) STRINGIZE_PRAGMA (GCC x)
#endif

PRAGMA(diagnostic push)
PRAGMA(diagnostic ignored "-Wpragmas")
PRAGMA(diagnostic ignored "-Wwhatever")
// some code here
PRAGMA(diagnostic pop)
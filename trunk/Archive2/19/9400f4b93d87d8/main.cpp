#define TESTING 1
#if defined(TESTING) && (TESTING == 1)
    #pragma error("HALP")
#endif
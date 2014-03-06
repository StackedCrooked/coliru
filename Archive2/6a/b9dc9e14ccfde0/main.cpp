#ifdef _RELEASE_
    #define FINAL_ON_RELEASE final
#else
    #define FINAL_ON_RELEASE
#endif

class T FINAL_ON_RELEASE { };
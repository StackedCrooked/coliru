//PP_FOR.hpp
#ifndef PP_FOR_MIN
#error PP_FOR_MIN NOT DEFINED
#endif
#ifndef PP_FOR_MAX
#error PP_FOR_MAX NOT DEFINED
#endif
#if PP_FOR_MAX < PP_FOR_MIN
#error PP_FOR_MIN CANNOT BE GREATER THAN PP_FOR_MAX
#endif

#ifdef PP_FOR_MIN
#ifndef PP_FOR_MIN1
    #if PP_FOR_MIN==PP_FOR_MAX
    #else if PP_FOR_MIN+1==PP_FOR_MAX
        PP_FOR_BODY
    #else 
        #define PP_FOR_MIN1 PP_FOR_MIN
        #define PP_FOR_MAX1 (PP_FOR_MAX-PP_FOR_MIN)/2
        #include "PP_FOR.hpp"
        #undef PP_FOR_MIN1
        #undef PP_FOR_MAX1    
        #define PP_FOR_MIN1 (PP_FOR_MAX-PP_FOR_MIN)/2
        #define PP_FOR_MAX1 PP_FOR_MAX
        #include "PP_FOR.hpp"
        #undef PP_FOR_MIN1
        #undef PP_FOR_MAX1
    #endif
#endif
#endif

#ifdef PP_FOR_MIN1
#ifndef PP_FOR_MIN2
    #if PP_FOR_MIN1==PP_FOR_MAX1
    #else if PP_FOR_MIN1+1==PP_FOR_MAX1
        PP_FOR_BODY
    #else 
        #define PP_FOR_MIN2 PP_FOR_MIN1
        #define PP_FOR_MAX2 (PP_FOR_MAX1-PP_FOR_MIN1)/2
        #include "PP_FOR.hpp"
        #undef PP_FOR_MIN2
        #undef PP_FOR_MAX2    
        #define PP_FOR_MIN2 (PP_FOR_MAX1-PP_FOR_MIN1)/2
        #define PP_FOR_MAX2 PP_FOR_MAX1
        #include "PP_FOR.hpp"
        #undef PP_FOR_MIN2
        #undef PP_FOR_MAX2
        #endif
#endif
#endif

#ifdef PP_FOR_MIN2
#ifndef PP_FOR_MIN3
    #if PP_FOR_MIN2==PP_FOR_MAX2
    #else if PP_FOR_MIN2+1==PP_FOR_MAX2
        PP_FOR_BODY
    #else 
        #define PP_FOR_MIN3 PP_FOR_MIN2
        #define PP_FOR_MAX3 (PP_FOR_MAX2-PP_FOR_MIN2)/2
        #include "PP_FOR.hpp"
        #undef PP_FOR_MIN3
        #undef PP_FOR_MAX3    
        #define PP_FOR_MIN3 (PP_FOR_MAX2-PP_FOR_MIN2)/2
        #define PP_FOR_MAX3 PP_FOR_MAX2
        #include "PP_FOR.hpp"
        #undef PP_FOR_MIN3
        #undef PP_FOR_MAX3
        #endif
#endif
#endif


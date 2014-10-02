#define createwrapper_single(f) \
    typedef wrapper<f> f##_wrapper;
#define createwrapper_multiple(f, ...) \
    typedef wrapper<f<__VA_ARGS__> > f##_wrapper;
    
#define pick_createwrapper(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, NAME, ...) NAME
#define createwrapper(...) \
    pick_createwrapper(__VA_ARGS__, createwrapper_multiple, createwrapper_multiple, \
    createwrapper_multiple, createwrapper_multiple, createwrapper_multiple, \
    createwrapper_multiple, createwrapper_multiple, createwrapper_multiple, \
    createwrapper_multiple, createwrapper_single, zero_argument_not_supported_anyway)(__VA_ARGS__)
    
createwrapper(normal_class)
createwrapper(templated_class,int)
createwrapper(templated_class2,int, double)
#ifndef deprecate
#ifdef _MSC_VER
#define deprecate __attribute__((deprecated))
#elif defined(__GNUC__)
#define deprecate __attribute__((deprecated)) 
#else
#define deprecate [[deprecated]]
#endif // VC++ || GCC || Others
#endif // deprecated

deprecate void blah ( int ) {
    
}

int main () {
    
}
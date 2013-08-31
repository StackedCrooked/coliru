#ifdef USE_IOSTREAM

    #include <iostream>
    
    int main(int argc, char**) {
        std::cout << argc;
    }

#else

    #include <stdio.h>
    
    int main(int argc, char**)
    {
        printf("%d", argc);
    }

#endif

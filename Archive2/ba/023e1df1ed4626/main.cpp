#ifndef TEXT
    #include <iostream>
 
    int main()
    {
    #define TEXT "Hello, world!"
    #include __FILE__
    #define TEXT "Hello again!"
    #include __FILE__
 
    }
#else
    std::cout << TEXT << '\n';
    #undef TEXT
#endif
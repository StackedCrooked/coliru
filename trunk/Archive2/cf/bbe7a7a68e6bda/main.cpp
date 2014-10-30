#include <iostream>
#include <vector>
 
int main()
{
    // typical loop with a single statement as the body
    for (int i = 0; i < 10; ++i)
        std::cout << i << ' ';
    std::cout << '\n';
 
    // init-statement can declare multiple names, as long as they
    // can use the same decl-specifier-seq
    for (int i=0, *p = &i; i < 9; i+=2) {
        std::cout << i << ':' << *p << ' ';
    }
    std::cout << '\n';
 
    // condition may be a declaration
    char cstr[] = "Hello";
    for(int n = 0; char c = cstr[n]; ++n)
        std::cout << c;
    std::cout << '\n';
 
    // init-statement can use the auto type specifier
    std::vector<int> v = {3, 1, 4, 1, 5, 9};
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        std::cout << *iter << ' ';
    }
    std::cout << '\n';
 
   // init-statement can be an expression
    int n = 0;
    for (std::cout << "Loop start\n";
         std::cout << "Loop test\n";
         std::cout << "Iteration " << ++n << '\n')
        if(n > 1)
            break;
    std::cout << '\n';
}
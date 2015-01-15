#include <iostream>
#include <string>

int main()
{
    int a = 8, b = 3;
    std::string c;
    bool first = true;
    while( b --> 0 ) {
        if( !first )
            c += '+';
        first = false;
        c += std::to_string(a);
    }
    std::cout << c;
}

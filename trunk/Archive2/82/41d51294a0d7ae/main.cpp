#include<iostream>
#include<fstream>
//#include<cstdlib>
//#include<iomanip>
#include <stack> // *** added
// using namespace std;

int main()
{
    std::ifstream fin( __FILE__ /* "txtfile.txt" */ );
    if( !fin.is_open() )
    {
        std::cerr << "\nFile Opening Error...\n";
        return 1 ;
    }
    std::stack<char> stk ;

    std::cout << "\nContents of file in original order:\n";
    char ch;
    while( fin.get(ch) )
    {
        std::cout << ch ;
        stk.push(ch) ;
    }

    std::cout << "\n\n=================\n\nContents of file in reverse order:\n";
    while( !stk.empty() )
    {
        std::cout << stk.top() ;
        stk.pop() ;
    }
    std::cout << '\n' ;
}

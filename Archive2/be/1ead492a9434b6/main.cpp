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
    while( fin.get(ch) ) // canonical
    {
        std::cout << ch ;
        stk.push(ch) ;
    }
    // note: the stram is in a failed/eof state here.
    // we don't need it any more, but if we did, 
    // we would have to first clear the state before using it
    // see: http://en.cppreference.com/w/cpp/io/basic_ios/clear
    

    std::cout << "\n\n=================\n\nContents of file in reverse order:\n";
    while( !stk.empty() )
    {
        std::cout << stk.top() ;
        stk.pop() ;
    }
    std::cout << '\n' ;
}

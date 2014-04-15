#include <iostream>
#include <string>
#include <vector>
#include <cctype>

int main()
{
    // string num1="";
    std::string num1 ;

    std::cout << "enter a number: ";
    std::cin >> num1 ;

    // int a[10];
    std::vector<int> a ; // http://www.mochima.com/tutorials/vectors.html

    // for (int i=0; i<10; i++)
    for( char c : num1 ) // http://www.stroustrup.com/C++11FAQ.html#for
    {
        // a[i]=stoi(num1.substr(i,i));

        // http://en.cppreference.com/w/cpp/string/byte/isdigit
        if( std::isdigit(c) ) a.push_back( c - '0' ) ;
        else std::cerr << "invalid character '" << c << "\n" ;
    }

    // for(int i=0;i<10;i++)
    for( int digit : a )
    {
        // cout<<a[i];
        std::cout << digit << ' ' ;
    }

    // system("pause");
    std::cout << "\npress enter to quit: " ;
    std::cin.ignore( 1000, '\n' ) ;
    std::cin.get() ;

    // return 0;
}

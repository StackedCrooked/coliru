#include <iostream>
#include <string>

struct friend_info
{
    friend_info() = default ;
    friend_info( std::string n, std::string i = "", int a = 0 )
            : name(n), interests(i), age(a) {}

    std::string name ;
    std::string interests ;
    int age = 0 ;

    bool nothing() const { return name.empty() && interests.empty() && age==0 ; }
};

void foo( const friend_info info[], std::size_t sz )
{
    for( std::size_t i = 0 ; i < sz ; ++i )
    {
        if( !info[i].nothing() )
        {
            // do something with it
            std::cout << "name: " << info[i].name << '\n' ;
        }
        else std::cout << "(nothing)\n" ;
    }
}

int main()
{
    friend_info information[] = { {}, {"xxxx", "y", 23}, {}, {"zzz"}, {} } ;
    information[0] = {"John Doe", "Sky Diving", 30} ;
    foo( information, sizeof(information) / sizeof( information[0] ) ) ;
}

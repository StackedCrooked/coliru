#include <iostream>
#include <boost/any.hpp>

enum Tag { X, Y, S };

struct Data
{
    int x         = -1;
    float y       = -1.0;
    std::string s = "unset";
};

// global
Data data_instance;


void receive_msg(std::pair<Tag, boost::any> && msg)
{
    auto & tag  = std::get<0>(msg);
    auto & data = std::get<1>(msg);

    #define macro_set(N)                                                        \
        do {                                                                    \
            data_instance.N = boost::any_cast<decltype(data_instance.N)>(data); \
        } while(0)

    switch(tag)
    {
        case X: macro_set(x); break;
        case Y: macro_set(y); break;
        case S: macro_set(s); break;
    };
}


int main(void)
{
    std::cout << "Before: "   << std::endl
              << "      x - " << data_instance.x << std::endl 
              << "      y - " << data_instance.y << std::endl 
              << "      s - " << data_instance.s << std::endl;

    receive_msg( {Tag::X, 5} );
    receive_msg( {Tag::Y, 3.14f} );
    receive_msg( {Tag::S, std::string("hello")} );

    std::cout << "After: "    << std::endl
              << "      x - " << data_instance.x << std::endl 
              << "      y - " << data_instance.y << std::endl 
              << "      s - " << data_instance.s << std::endl;
}

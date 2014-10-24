#include <iostream>
#include <vector>
#include <boost/any.hpp>

enum Tag { X, Y, S, CH1, CH2, C1, C2 };

struct Data
{
    int x                             = -1;
    float y                           = -1.0;
    std::string s                     = "unset";
    std::vector<std::string> choices1 = {};
    std::vector<std::string> choices2 = {};
    std::string choice1               = "unset";
    std::string choice2               = "unset";
};

// global
Data data_instance;


void receive_msg(std::pair<Tag, boost::any> && msg)
{
    auto & tag  = std::get<0>(msg);
    auto & data = std::get<1>(msg);

// set single items
#define macro_set(N)                                                        \
    do {                                                                    \
        data_instance.N = boost::any_cast<decltype(data_instance.N)>(data); \
    } while(0)
        
        
// set items that depend on another, in this case search
#define macro_dep(Dep, N)                                                                \
    do {                                                                                 \
        auto && _data  = boost::any_cast<decltype(data_instance.Dep)::value_type>(data); \
        auto ret = std::find(data_instance.Dep.begin(),                                  \
                             data_instance.Dep.end(),                                    \
                             _data);                                                     \
        if (ret != data_instance.Dep.end()) {                                            \
            macro_set(N);                                                                \
        }                                                                                \
    } while(0)
        

    switch(tag)
    {
        case X:   macro_set(x); break;
        case Y:   macro_set(y); break;
        case S:   macro_set(s); break;
        case C1:  macro_dep(choices1, choice1); break;
        case C2:  macro_dep(choices2, choice2); break;        
        case CH1: macro_set(choices1); break;
        case CH2: macro_set(choices2); break;
    };
}


int main(void)
{
    // setup choices first
    receive_msg( {Tag::CH1, std::vector<std::string>{"1","2","3"}} );
    receive_msg( {Tag::CH2, std::vector<std::string>{"a","b","c"}} );
    
    receive_msg( {Tag::X, 5} );
    receive_msg( {Tag::Y, 3.14f} );
    receive_msg( {Tag::S, std::string("hello")} );
    receive_msg( {Tag::C1, std::string("2")} );
    receive_msg( {Tag::C2, std::string("c")} );

    std::cout << "x  - " << data_instance.x << std::endl 
              << "y  - " << data_instance.y << std::endl 
              << "s  - " << data_instance.s << std::endl
              << "c1 - " << data_instance.choice1 << std::endl
              << "c2 - " << data_instance.choice2 << std::endl;
}

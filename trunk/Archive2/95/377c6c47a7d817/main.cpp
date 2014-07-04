#include <iostream>
#include <string>
#include <vector>

#include <boost/proto/proto.hpp>
#include <boost/proto/debug.hpp>

struct ResetTag {};
const boost::proto::terminal<ResetTag>::type reset = {};
struct ShiftTag {};
const boost::proto::terminal<ShiftTag>::type shift = {};

int main()
{
    boost::proto::display_expr(
        reset((2 + 8) / 2 - shift([](int i) {
            std::cout << i << std::endl;
        }))
        
    );
    
    auto f = reset([](int i) -> void {
            std::cout << i << std::endl; 
        });
    
    //boost::proto::default_context ctx;
    boost::proto::value(boost::proto::right(f))(24342);
}

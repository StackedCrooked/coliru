#include <stdint.h>
#include <iostream>


namespace Futile {


struct Protocol {};
    
    
template<typename CLP>
struct BasicProtocol : Protocol
{
    template<typename Decoder>
    void pop(const Decoder & decoder)
    {
        static_cast<CLP&>(*this).do_pop(decoder);
    }
};
    
    
} // namespace Futile


namespace Futile {
namespace Eth {

struct Decoder {};
struct Session {};


struct Protocol : BasicProtocol<Protocol>
{
    void do_pop(const Decoder & dec)
    {        
    }        
};


} } // namespace Futile::Eth


namespace Futile {
namespace IPv4 {

struct Decoder {};
struct Session {};

template<typename HLP = Futile::Protocol>
struct Protocol : BasicProtocol<Protocol>
{
    void do_pop(const Decoder &)
    {
    }        
};


} } // namespace Futile::IPv4


int main()
{
}



//aa
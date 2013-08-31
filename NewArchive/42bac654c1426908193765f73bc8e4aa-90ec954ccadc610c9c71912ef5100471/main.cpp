#include <iterator>

namespace ns {

struct adl_hook {};

template<typename T>
void begin(T&)
{}

namespace subns {

struct range {
    template <typename=adl_hook>
    struct subrange_ {};
    
    using subrange=subrange_<>;
};

} // subns

} // ns

int main()
{
    using R = ns::subns::range::subrange;
    R subr;
    
    begin(subr);
}
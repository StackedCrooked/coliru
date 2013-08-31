#include <iterator>

namespace ns {

template<typename T>
void begin(T&)
{}

namespace subns {

// Fix?
// using ns::begin;

struct range {
    struct subrange {};
};

} // subns

} // ns

int main()
{
    using R = ns::subns::range::subrange;
    R subr;
    
    using std::begin;
    begin(subr);
}
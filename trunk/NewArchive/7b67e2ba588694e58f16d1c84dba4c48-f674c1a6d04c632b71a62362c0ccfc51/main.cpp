#include <iostream>
#include <boost/optional.hpp>

struct SeqNum
{
    // Note: there is no default constructor because that could lead to bugs.
    explicit SeqNum(uint32_t value) : value_(value) {}

    friend bool operator<(SeqNum lhs, SeqNum rhs)
    {
        return static_cast<int32_t>(lhs.value_ - rhs.value_) < 0;
    }
    
    uint32_t value_;
};


int main()
{
    SeqNum a{1};
    boost::optional<SeqNum> b;
    return a < b;
}
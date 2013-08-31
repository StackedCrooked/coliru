#include <iostream>
#include <boost/optional.hpp>

struct SeqNum
{
    explicit SeqNum(uint32_t value) : value_(value) {}
    
    uint32_t value_;
};

inline bool operator<(SeqNum lhs, SeqNum rhs)
{
    std::cout << lhs.value_ << " < " << rhs.value_ << "?" << std::endl;
    return static_cast<int32_t>(lhs.value_ - rhs.value_) < 0;
}

int main()
{
    SeqNum a{0};
    boost::optional<SeqNum> b; // unset
    std::cout << (a < b ? "a < b" : "a >= b") << std::endl;
}
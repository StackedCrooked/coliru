#include <iostream>

enum class CSide {
    NONE = 0,
    BID = 1,
    BUY = 1,
    SELL = -1,
    ASK = -1,
};

std::ostream&
operator<<(std::ostream& os, const CSide& side) {
    switch(side) {
        case CSide::NONE:
            return os << "None";
        case CSide::BID:
            return os << "Bid";
        case CSide::ASK:
            return os << "Ask";
        default:
            throw std::exception();
    }
}

int main()
{
    CSide none;
    CSide bid = CSide::BID;
    CSide ask = CSide::ASK;
    CSide sell = CSide::SELL;

    std::cout << none << std::endl
        << bid << std::endl
        << ask << std::endl
        << sell << std::endl;
}
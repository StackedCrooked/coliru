#include <boost/any.hpp>

struct t { };

template<typename T>
boost::any& operator<(t&, T&) {
    static boost::any x;
    return x;
}

template<typename T>
boost::any& operator>(T&, t&) {
    static boost::any x;
    return x;
}

int main() {
    auto i = new int();
    t Ptr, Node, node;
    Ptr<Node> node = *i;
    return 0;
}
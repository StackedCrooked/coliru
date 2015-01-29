#include <boost/function.hpp>
int main() {
    boost::function<int()> foo;
    foo = nullptr;
}
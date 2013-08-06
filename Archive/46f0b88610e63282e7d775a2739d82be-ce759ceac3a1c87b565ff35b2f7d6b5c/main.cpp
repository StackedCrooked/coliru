#include <iostream>
#include <string>
#include <boost/lockfree/queue.hpp>

struct thing {
    int a;
    std::string b;
};

int main() {
    boost::lockfree::queue<thing> things;
}

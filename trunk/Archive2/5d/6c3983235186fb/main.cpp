#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> messages(100, "Hello, world!\n");

    std::copy(messages.begin(), messages.end(), std::ostream_iterator<std::string>(std::cout));

    return 0;
}

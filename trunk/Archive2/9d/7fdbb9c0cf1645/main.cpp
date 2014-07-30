
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>

struct useless_deleter {
    void operator()(...) const {
        std::cout << "useless benfica" << std::endl;
    }
};

int main()
{
   using ptr_type = std::unique_ptr<int, useless_deleter>;
   std::vector<ptr_type> asd;
   asd.push_back(ptr_type{new int(0)});
}
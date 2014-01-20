#include <ostream>   // for std::ostream
#include <iostream>  // for std::cout

struct Node
{
   int key;
   int value;
};

std::ostream& operator<<(std::ostream& os, const Node& n) {
    return os << n.key << ':' << n.value;
}

int main()
{
   Node n{3,5};
   std::cout << n << '\n';
}
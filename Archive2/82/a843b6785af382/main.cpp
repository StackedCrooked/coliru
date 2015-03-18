#include <iostream>

namespace TextSearch {
class Node;

class LookupTable {
    public:
        LookupTable ();
        ~LookupTable ();
        
        void add (const char*);
        bool isPresent (const char*);
    private:
        Node* root_;
};


class Node {
    public:
        Node ();
        
    private:
        static const size_t size_ = ('z' - 'a' + 1)*2;
        Node* edges_ [size_];
};

}

int main()
{
  
    std::cout << "!!!" << std::endl;
}

#include <iostream>

namespace TextSearch {
class Node;

class LookupTable {
    public:
        LookupTable ();
        ~LookupTable ();
        
        void add (const char*);
        bool isExist (const char*) const;
    private:
        Node* root_;
};


class Node {
    public:
        Node ();
        Node& child (char);
        bool isLeaf (char) const;
        Node& childAdd (char);
    private:
        static const size_t size_ = ('z' - 'a' + 1)*2;
        Node* edges_ [size_];
};

LookupTable::LookupTable (): root_ (new Node ()) {
}

LookupTable::~LookupTable () {
    delete root_;
}

void LookupTable::add (const char* str) {
    if (!str) { 
        return;
    }
    
    Node& current = *root_;
    while ('\0' != *str) {
        current = current.childAdd (*str++);    
    }
}

bool LookupTable::isExist (const char* str) const {
    
}

} //namespace TextSearch

int main()
{
  
    std::cout << "" << std::endl;
}

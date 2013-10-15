#include <iostream>
#include <cstring>

class Node {
public:

        /* Enumeration */

        enum NAVIGATION {
            RIGHT = 0, 
            UP = 1, 
            LEFT = 2, 
            DOWN = 3
        };
};

class NodeConnection {
    public:

    NodeConnection (Node* a, Node* b, Node::NAVIGATION initial_nav);

};

int main()
{
    
    return 0;
}


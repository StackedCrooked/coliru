
#include <iostream>
using namespace std;

class Wrap {
    int id;

    static int create() { static int count = 0; return ++count; }
    static void destroy(int id) { cout << "destroy called on :" << id << endl; }
    
public:
    void print() { cout << id << endl; }

    Wrap() : id{create()} {}
    
    // LOOK HERE ---------------------------------------------------
    // 
    Wrap(Wrap&& wrap) : id((destroy(id), wrap.id)) { wrap.id = 0; }
    // --------------------^^^^^^^^^^^^^^^^^^^^---------------------
};


int main() {
    Wrap a, b;
    a.print();
    b.print();
    
    Wrap c (std::move(b));
    
    a.print();
    b.print();
    c.print();
}
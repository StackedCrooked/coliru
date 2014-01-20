
#include <iostream>

using namespace std;

struct Hello {
    struct Something {
        void print() const {
            cout << "Something::print" << endl;
        }
    };
    
    struct Tada {
        void print() const { cout << "TadaNew" << endl; }
    };
    
    static Tada Something() {
        return Tada();
    };
};

void fooNew(const struct Hello::Something& some) {
    some.print();
}

int main() {
    
    Hello::Something().print();
    
    struct Hello::Something a;
    a.print();
    
    // (struct Hello::Something()).print(); // error: 
    
    (new struct Hello::Something)->print();
    
    fooNew(a);
    //fooNew(struct Hello::Something()); // error
    //fooNew(Hello::Something()); // error
        
    return 0;
}
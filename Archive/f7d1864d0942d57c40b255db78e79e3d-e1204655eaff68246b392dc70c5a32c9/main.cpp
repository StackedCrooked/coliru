#include <memory>

using namespace std;

struct A {
    virtual ~A() {}
};
struct B : A {};

shared_ptr<A> getSharedPointer() {
    return make_shared<B>();
}

#include <iostream>

int main() {
    shared_ptr<B> storage = nullptr;
    
    if (true)
    {
      shared_ptr<A> definition = getSharedPointer();
    
      // Store the lambda
      storage = dynamic_pointer_cast<B>(definition);
    }
    
    cout << storage.get() << endl;
}

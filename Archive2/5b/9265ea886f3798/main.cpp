#include <iostream>
#include <unordered_set>

struct waterContainer {
    virtual void VirtualfunctionA() const = 0;
};

struct bottle : waterContainer {
    void VirtualfunctionA() const override {
        std::cout << "I'm a bottle\n";
    }
};

struct jug : waterContainer {
    void VirtualfunctionA() const override {
        std::cout << "I'm a jug\n";
    }
};

int main() {
    std::unordered_set<waterContainer*> collection;
    bottle b1;
    jug j1;
    waterContainer* ptr1 = &b1;
    waterContainer* ptr2 = &j1;
    collection.insert(ptr1);
    collection.insert(ptr2);
    (*collection.find(ptr1))->VirtualfunctionA(); //calls bottle implementation
    (*collection.find(ptr2))->VirtualfunctionA(); //calls jug implementation 
}

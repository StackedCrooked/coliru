#include <iostream>

class BaseContainer {
public:
    virtual ~BaseContainer() {}
};

template <typename T>
class Container : public BaseContainer
{
    private:
    T data;
    public:
    Container(T newData) : data(newData) {}
    T getData() {return data;}
};

int main() {
    BaseContainer *numContainer = new Container<int>(5);
    
    Container<int> *ptr = dynamic_cast<Container<int>*>(numContainer);
    if(ptr) std::cout << ptr->getData() << std::endl;;
    delete numContainer;
}
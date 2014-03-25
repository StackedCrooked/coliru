#include <iostream>
#include <memory>
#include <vector>

#define VIRTUAL

struct Data {
    int x;
};

struct Object {
    std::unique_ptr<Data> data;
    
    Object(std::unique_ptr<Data> input) : data(std::move(input)) { }
    Object() : Object(std::unique_ptr<Data>{}) { }
        
    Object(Object&&) = default;
    
    virtual ~Object() { }

    virtual void describe()
    { }
};

int main(int, char *[])
{
    std::vector<Object> objects;
    objects.push_back(Object{});
    return 0;
}

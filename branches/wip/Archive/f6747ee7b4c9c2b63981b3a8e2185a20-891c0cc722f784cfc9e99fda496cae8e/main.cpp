#include <iostream>
#include <memory>
#include <set>

struct MyType {
    int x;
    MyType()=default;
    MyType(const MyType&)=default;
    MyType(MyType&&)=default;
    MyType(int v) :x(v) {}
    MyType&operator=(const MyType&)=default;
    MyType&operator=(MyType&&)=default;
};

struct MyTypeCompare
{
  bool operator()(const std::shared_ptr<MyType> lhs, const std::shared_ptr<MyType> rhs) const
    {
        if(lhs->x!=rhs->x)
            return lhs->x<rhs->x; 
        return lhs<rhs;
    }
};

int main() {
    std::set<std::shared_ptr<MyType>, MyTypeCompare> data;
    auto ptr = std::make_shared<MyType>(2);
    data.insert(ptr);
    data.insert(ptr);
    data.insert(ptr);
    data.insert(ptr);
    data.insert(ptr);
    data.insert(ptr);
    auto ptr2 = std::make_shared<MyType>(2);
    data.insert(ptr2);
    data.insert(ptr2);
    data.insert(ptr2);
    data.insert(ptr2);
    auto ptr3 = std::make_shared<MyType>(3);
    data.insert(ptr3);
    
    for(auto& ref : data)
        std::cout << ref->x << '\n';
}
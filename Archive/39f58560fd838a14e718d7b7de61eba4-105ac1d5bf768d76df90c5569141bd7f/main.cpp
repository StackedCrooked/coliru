#include <iostream>
#include <vector>
#include <functional>

struct Parent{
};

struct Child1 : public Parent{
};

struct Child2 : public Parent{
};

template <typename T, typename Parent>
Parent* factory(){
    return new T;
}

std::vector<std::function<Parent*()> > vec;

int main(){
    vec.push_back(&factory<Child1, Parent>);
    vec.push_back(&factory<Child2, Parent>);
}

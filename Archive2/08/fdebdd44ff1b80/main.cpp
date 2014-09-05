#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

#include <memory>
#include <functional>
#include <sstream>

#include <numeric>

#include <unordered_map>
#include <future>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

class MapObject {
public:
    virtual ~MapObject(){}
};

class Circle : public virtual MapObject {
};

class Placemark : public virtual MapObject {
};

void foo(Placemark*)
{
    printf("foo(Placemark)");
}

void foo(Circle*)
{
    printf("foo(Circle)");
}

class MapObjectImpl : virtual public MapObject {
};

class CircleImpl : public MapObjectImpl, public Circle {
public:
    CircleImpl() { foo(this); }
};

class PlacemarkImpl : public MapObjectImpl, public Placemark {
public:
    PlacemarkImpl() { foo(this); }
};

class A {
public:
     A(int a) : a(a){}
    ~A() { printf("~A()\n"); }
    int a;
};

struct Deleter {
    void operator()(A* ptr) { printf("Deleter()\n"); };
};


A* release(std::shared_ptr<A> sp)
{
    std::shared_ptr<A> newSp(nullptr, Deleter());
    sp.swap(newSp);
    return newSp.get();
}

A* testRelease() 
{
    std::shared_ptr<A> sp = std::make_shared<A>(5);
    return release(sp);
}

int main()
{
    printf("%d", testRelease()->a);
    std::shared_ptr<A> tmp(nullptr/*, Deleter()*/);
    return 0;
}
   
    

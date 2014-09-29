#include <vector>

template<typename T>
struct Foo {};

using Foo<int> = IntFoo;
using Foo<double> = DoubleFoo;

template<typename T>
void doSomething(Foo<T>) {
}

template<template<typename> TemplT>
struct GenericThing {
    template<typename T>
    GenericThing(T t) {
        static_assert(/*T is an instantiation of TemplT*/, "Must blah");   
    }
};

int main() {
    std::vector<GenericThing<Foo>> foos{IntFoo{}, DoubleFoo{}};
    for (auto foo : foos) {
        foo.apply(doSomething);   
    }
}
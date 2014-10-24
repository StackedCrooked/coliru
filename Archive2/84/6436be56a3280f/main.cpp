template<class Context> class Trait1_Foobish {};

class Aspect_Foobish
{
public:
    template<class Context>
    using Trait1Policy = Trait1_Foobish<Context>;
};

template<template<class> class Trait1>
class Entity {};

template<class Aspect>
using Entity_Aspectual = Entity<Aspect::template Trait1Policy>;

int main()
{
    Entity_Aspectual<Aspect_Foobish> foobishEntity;

    return 0;
}
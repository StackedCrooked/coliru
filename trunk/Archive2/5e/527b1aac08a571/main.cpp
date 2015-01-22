#include <iostream>


struct AnimationInterface {
    inline virtual ~AnimationInterface() {}
};

struct AbstractAnimationRealization : AnimationInterface {
    bool removeAtEnd;
};


struct Void {};

struct MutatorTypeStorage_MutatorTypeIsVoid {
    Void mutator;  
};

struct MutatorTypeStorage_SizeOptimized {};


struct Inh11 : 
    AbstractAnimationRealization, 
    MutatorTypeStorage_MutatorTypeIsVoid 
{};

struct Inh21 : 
    AbstractAnimationRealization, 
    MutatorTypeStorage_SizeOptimized 
{};

struct Inh12 : 
    AbstractAnimationRealization, 
    MutatorTypeStorage_MutatorTypeIsVoid 
{int* p;};

struct Inh22 : 
    AbstractAnimationRealization, 
    MutatorTypeStorage_SizeOptimized 
{int* p;};


int main() {
    std::cout << sizeof(MutatorTypeStorage_MutatorTypeIsVoid) << std::endl;
    std::cout << sizeof(MutatorTypeStorage_SizeOptimized) << std::endl;
    std::cout << sizeof(AbstractAnimationRealization) << std::endl;
    std::cout << sizeof(Inh11) << std::endl;
    std::cout << sizeof(Inh21) << std::endl;
    std::cout << sizeof(Inh12) << std::endl;
    std::cout << sizeof(Inh22) << std::endl;
}
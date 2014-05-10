#include <vector>
#include <algorithm>
#include <iostream>

template<typename Type>
class Predicate{
public:
    Predicate() {};
    virtual ~Predicate(){};
    virtual bool operator()(const Type & value) = 0;
    virtual bool operator()(const Type * value){ //<-- this is the operator thats not working
        return (*this)(*value);
    };
};

template<typename Type>
class Always : public Predicate<Type>{
public:
    using Predicate<Type>::operator();
    bool operator()(const Type & value){return true;}
    ~Always(){};
};

int main(){
    Always<int> a;
    int i = 1000;
    a(&i);
}
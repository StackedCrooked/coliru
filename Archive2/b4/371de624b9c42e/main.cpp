#include <iostream>
#include <typeinfo>


class A{
protected:
    virtual void printClassInfo(const std::type_info & dInfo) = 0;
};

class B: public A{
protected:
    void printClassInfo ( const std::type_info& dInfo ){
        std::cout<<"Got "<<dInfo.name()<<std::endl;
    }
};

template<typename type> class TypedA: public A{
public:
    inline void print(){
        printClassInfo(typeid(type));
    }
};

int main(int argc, char* argv[]){

    A * a=new B;
    TypedA<int> * test=reinterpret_cast<TypedA<int> *>(a);

    test->print();

    return 0;
}

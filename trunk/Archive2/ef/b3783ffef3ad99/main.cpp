#include <iostream>
#include <type_traits>

struct MyClass {
    virtual void debug () const {
        std::cerr << "MyClass" << std::endl;
    };
};

struct MyClassDer : public MyClass {
    virtual void debug () const {
        std::cerr << "MyClassDer" << std::endl;
    };
};

template <typename T, typename Requires = typename std::enable_if<!std::is_base_of<MyClass, T>::value, void>::type > 
void  func  (const T& t) {
    std::cerr << "func template" << std::endl;
}

void func (const MyClass& myClass) {
    std::cerr << "func overloaded" << std::endl;
    myClass.debug ();
}


int main(int argc, char **argv) {
    func (1);
    MyClass myClass;
    func (myClass);
    MyClassDer myClassDer;
    func(myClassDer);
}
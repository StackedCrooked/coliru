#include <iostream>

template<typename T>
class MyClass {
    public:
        // Public function calls private bar
        void foo() { bar(baz); }
    
        MyClass(T val) : baz(val) {}
    private:
        struct MyStruct {
            int val_;
            MyStruct(T val) : val_(val) {}
        };
    
        MyStruct baz;   
        MyStruct bar(MyStruct qux);
};

template<typename T>
typename MyClass<T>::MyStruct MyClass<T>::bar(MyStruct qux) {
    std::cout << qux.val_ << std::endl;
    qux.val_++;
    std::cout << qux.val_ << std::endl;
    return qux;
}

int main() {
    MyClass<int> c(1);

    c.foo();

    return 0;
}

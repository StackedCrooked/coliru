#include<memory>

class MyClass { };

int main() {

std::auto_ptr<MyClass> myPtr(new MyClass);

}
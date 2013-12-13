class Base {};
class Derived : public Base {};

char memory[100];
new(memory) Derived();
Base* ptr = (Base*)memory;
ptr->~Base();
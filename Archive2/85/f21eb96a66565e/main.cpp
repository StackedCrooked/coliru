struct Base
{
    int a;
    
    Base(const Base& other) { a = other.a; }
};

struct A : public Base {};

struct B : public Base {};

int main()
{
    A a{B()};
    
    return 0;
}
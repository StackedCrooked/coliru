

struct A { };


struct B
{
    B() { }
};


int main()
{
    A a; // warning: unused variable
    B b; // (silence)
}

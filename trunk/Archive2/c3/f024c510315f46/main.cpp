void foo() = delete;

struct A
{
    ~A() = delete;
};

struct B : A
{
    A a;
    B(){ };
    B(const B&&)  = delete;
};

B *b = new B;

int main() {
}
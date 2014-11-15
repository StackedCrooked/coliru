struct A
{
    ~A() = delete;
    A(){ }
};

struct B : A
{
    B() = default;
    ~B() = delete;
};

//B b;

int main() {
}
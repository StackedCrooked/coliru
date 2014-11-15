struct A
{
    ~A() = delete;
    A(){ }
};

struct B : A
{
    B(){ };
    ~B(){ };
};

//B b;

int main() {
}
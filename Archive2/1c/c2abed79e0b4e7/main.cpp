struct A 
{
    A() noexcept {};
    ~A() = delete;
 };

struct B : A {
    B() noexcept {};
};

int main() {
}


struct A 
{
    A() noexcept { };
//    private:
    ~A() = delete;
 };

struct B : A {
    B() noexcept {};
};

int main() {
}

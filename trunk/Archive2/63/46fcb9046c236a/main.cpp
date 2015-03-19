#define DEBUG_A true
#define DEBUG_B false

void f() noexcept(DEBUG_A) {}
void g() noexcept(DEBUG_B) {}

int main()
{
    static_assert(noexcept(f()), "!");
    static_assert(!noexcept(g()), "!");
}

void foo() noexcept {}
void bar() { throw "what?"; }

int main()
{
        void (*t)() noexcept = foo;
        void (*q)() noexcept = bar;
}
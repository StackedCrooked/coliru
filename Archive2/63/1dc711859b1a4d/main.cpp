void foo() noexcept {}

int main()
{
        void (*p)() noexcept = foo;
        
        (void)p;
}
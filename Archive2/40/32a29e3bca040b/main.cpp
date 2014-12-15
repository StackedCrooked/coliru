
void foo(void*) noexcept {}
void bar(void*)          {}

void (*foo_ptr)(void *) noexcept = nullptr;
using function_type = decltype(foo_ptr);

int main()
{
    function_type f = foo;
    function_type b = bar;
}

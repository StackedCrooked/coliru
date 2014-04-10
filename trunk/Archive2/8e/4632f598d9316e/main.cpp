class __attribute__((deprecated)) old_style_throw_specification;
class old_style_throw_specification {};

#define throw(...) throw(old_style_throw_specification, __VA_ARGS__)

void f()
{
    throw 42;
}

void g() throw(int)
{
    throw 42;
}

int main()
{    
}

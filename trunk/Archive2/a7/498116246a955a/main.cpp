namespace many {
namespace namespaces {
    class Bar { };

    template<typename T>
    void foo() { }
}
}

#define EASYCALL(expr)\
    do\
    {\
        using Bar = many::namespaces::Bar;\
        expr;\
    } while (false)
 
int main()
{
    EASYCALL(many::namespaces::foo<Bar>());
}
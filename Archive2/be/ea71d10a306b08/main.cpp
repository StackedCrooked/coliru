template<typename myEnumType>
int foo(const myEnumType &)
{
    return 42;
}

int main()
{
    typedef enum {AAA, BBB} myEnumType;
    myEnumType enum_type_istance;
    int a = foo(enum_type_istance);
    (void)a;
}
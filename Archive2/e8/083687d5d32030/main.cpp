template <typename Type>
Type Foo(Type::iterator First, Type::iterator Last)
{
    Type Result;
    for (Type::iterator i = First; i != Last; i++)
    {
        if (...)
        {
           Result.push_back(*i);
        }
    }
    return Result;
}
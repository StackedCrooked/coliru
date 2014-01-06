#include <string>

template <typename TT> TT getAs();
template <>            std::string getAs() { return "bye"; }
template <>            int getAs() { return 123; }

class Foo
{
public:
    template <typename TT>
        TT getAs() const { return ::getAs<TT>(); }

    template <typename TT>
        operator TT() const { return ::getAs<TT>(); }
};

Foo tempFoo() { return Foo(); }

int main()
{
    Foo foo;
    std::string testStringLocal = foo;                            // OK in 2010, FAIL in 2012
    int testIntTemp = tempFoo();                                  // OK
    std::string testStringTemp = tempFoo().getAs<std::string>();  // OK
    const std::string& testStringTemp2 = tempFoo();               // OK

    std::string testStringTemp3 = tempFoo();                    // FAIL!
}

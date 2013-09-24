#include <string> 

struct X
{
    int         has_some_properties;
    std::string data;
};

// now, for our named instances:

// define some character arrays **with external linkage**
namespace Names
{
    extern const char Vanilla[] = "Vanilla";
    extern const char Banana [] = "Banana";
    extern const char Coconut[] = "Coconut";
    extern const char Shoarma[] = "Shoarma";
}

// now we can "adorn" a `namedX` with the name constants (above)
template <const char* Name>
   struct NamedX
{
    static X value;
};

template <const char* const Name> X NamedX<Name>::value;

int main()
{
    X& vanilla = NamedX<Names::Vanilla>::value;

    vanilla = { 42, "Woot!" };

    return vanilla.has_some_properties;
}

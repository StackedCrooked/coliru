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
    struct Vanilla final { static const char* name() { return "Vanilla"; } };
    struct Banana  final { static const char* name() { return "Banana";  } };
    struct Coconut final { static const char* name() { return "Coconut"; } };
    struct Shoarma final { static const char* name() { return "Shoarma"; } };
}

// now we can "adorn" a `namedX` with the name constants (above)
template <typename Tag> struct NamedX
{
    static X value;
};

template <typename Tag> X NamedX<Tag>::value;

int main()
{
    X& vanilla = NamedX<Names::Vanilla>::value;
    vanilla = { 42, "Woot!" };
    return vanilla.has_some_properties;
}

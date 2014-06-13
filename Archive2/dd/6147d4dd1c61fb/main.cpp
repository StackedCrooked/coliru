#include <type_traits>
struct cat
{
    cat() = default;
    cat(cat const&) = default;
    
    cat(cat&&) = default;
    cat(cat&&, ...) {};
};

cat meow() { cat c; return c; }
cat purr() { cat c; return static_cast<cat&&>(c); }

int main()
{
    meow();
    purr();
}
#include <type_traits>
struct cat
{
    cat() = default;
    cat(cat const&) = default;
    
    cat(cat&&) = default;
    cat(cat&&, ...) {};
};

cat meow() { return cat{}; }

int main()
{
    meow();
}
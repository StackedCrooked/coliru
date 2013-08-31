template <typename T> struct Trait;
template <typename T> struct TraitUser {};

class A
{
private:
    class B:TraitUser<B>
        {};
};


template<>
struct Trait<A::B>
{};

namespace ns {

template<typename... Tags> struct tagged_variant {};

void test(tagged_variant<struct blue>)
{}

} // ns

int main()
{
    test(ns::tagged_variant<struct blue> {});
}
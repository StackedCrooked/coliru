
#include <iostream>
#include <type_traits>
#include <utility>
#include <string>
#include <sstream>
#include <memory>

using namespace std;

struct TypeTraitsBase{};

template <class T>
struct TypeTraits
{
};

template <>
struct TypeTraits<int> : public TypeTraitsBase
{
string Serialize(int value, int x = 0 )
{
ostringstream out;
out << "{Serialize int[" << value << "], x[" << x <<"]}";
return out.str();
}
};
struct Exp 
{
template <class TValue, class TTraits = TypeTraits<typename decay<TValue>::type>, class... TArgs>
static
//decltype(auto)
auto
Serialize(
TValue&& value,
typename enable_if<std::is_base_of<TypeTraitsBase, TTraits>::value, TTraits&&>::type traits,
TArgs&&... args)
-> decltype(traits.Serialize(forward<TValue>(value), forward<TArgs>(args)...))
{
return traits.Serialize(forward<TValue>(value), forward<TArgs>(args)...);
}

template <class TValue, class TTraits = TypeTraits<typename decay<TValue>::type>, class... TArgs>
static
//decltype(auto)
auto
Serialize(
TValue&& value,
TArgs&&... args)
-> decltype(Serialize(forward<TValue>(value), TTraits{}, forward<TArgs>(args)...))
{
return Serialize(forward<TValue>(value), TTraits{}, forward<TArgs>(args)...);
}

};

int main()
{
cout << "Hello World" << endl;
cout << Exp().Serialize(42) << endl;
cout << Exp().Serialize(42, 2) << endl;
cout << Exp().Serialize(42, TypeTraits<int>{}) << endl;
cout << Exp().Serialize(42, TypeTraits<int>{}, 2) << endl;
}
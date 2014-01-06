// BUG #1
// infinite recursion trying to instantiate `auto func ()`
// clangs accepts (as expected)
struct A {};

template<typename>
int func (A) {
  return {};
}

template<typename T>
auto func () -> decltype (func<T> (A{})) {
  return {};
}

int
main (int argc, char *argv[])
{
  func<int> ();
}

// *********************************************************************

// BUG #2
// well we discussed this yesterday, but gcc refuses, clang accepts
template<typename... Args> struct foo { };
template<typename T, typename... Args> using bar = foo<T, Args...>;
template<typename T, typename... Args> using baz = bar<Args..., T>;

int
main (int argc, char *argv[])
{

}
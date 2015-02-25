#include <iostream>
#include <utility>
#include <type_traits>
#include <string>
#include <vector>

using namespace std;

struct error_type{};

template <class T>
class has_empty
{
   template<class U, class = typename std::enable_if<std::is_member_pointer<decltype(&U::empty)>::value>::type>
      static std::true_type check(int);
   template <class>
      static std::false_type check(...);
public:
   static constexpr bool value = decltype(check<typename std::remove_reference<T>::type>(0))::value;
//    static constexpr bool value = decltype(check<T>(0))::value;
};

template <bool invalid, class T, typename E = void>
struct valid {};

template <class T, typename E>
struct valid<false, T, E>
{
   static inline T&& check(T&& toCheck, const E& toThrow)
   {
      if (!toCheck)
        std::cout << "NoEmpty Throw" << '\n';
      else
        std::cout << "NoEmpty valid" << '\n';
      return std::forward<T>(toCheck);
   }
};

template <class T, typename E>
struct valid<true, T, E>
{
   static inline T&& check(T&& toCheck, const E& toThrow)
   {
      if (toCheck.empty())
        std::cout << "HasEmpty Throw" << '\n';
      else
        std::cout << "HasEmpty valid" << '\n';
      return std::forward<T>(toCheck);
   }
};

template<typename T
   , typename E
   , typename  = typename std::enable_if<std::is_base_of<error_type, E>::value>::type>
   inline T&& do_check(T&& toCheck, const E& toThrow)
{
   return valid<has_empty<T>::value, T, E>::check(std::forward<T>(toCheck), toThrow);
}

struct HasEmpty
{
    bool empty() {return false;}
};

struct NoEmpty
{
};


int main()
{
    error_type e;

    cout << has_empty<std::wstring>::value << '\n';
    cout << has_empty<std::vector<std::wstring>>::value << '\n';
    cout << has_empty<int>::value << '\n';
    cout << has_empty<HasEmpty>::value << '\n';
    cout << has_empty<NoEmpty>::value << '\n';

    do_check(true, e);
    do_check(false, e);

    do_check(std::string("45"), e);
    do_check(HasEmpty(), e);
    do_check(std::vector<bool>(), e);
    HasEmpty he;
    do_check(std::move(he), e);
    do_check(he, e); // does not work, has_empty<T>::value is 0
}

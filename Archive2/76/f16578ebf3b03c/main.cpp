#include <tuple>
#include <utility>
#include <type_traits>

class Widget{};

template <typename... T>
std::tuple<T...> capture_tuple(T&&... t) {
    return std::tuple<T...>{std::forward<T>(t)...};
}

int main()
{
  Widget w;
  auto list  = capture_tuple(
    w,
    Widget()
  );
  auto list2 = capture_tuple(
    Widget(),
    w
  );

  auto&& l  = std::get<0>(list);
  auto&& l2 = std::get<0>(list2);

  static_assert(std::is_same<decltype(list), std::tuple<Widget&, Widget>>::value,
                "Jabberwocky is killing user.");
  static_assert(std::is_same<decltype(list2), std::tuple<Widget, Widget&>>::value,
                "Jabberwocky is killing user.");
}

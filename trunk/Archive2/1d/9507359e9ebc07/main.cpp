#include <type_traits>

template <int placeholder, typename... Args>
struct mytype {};

using type = mytype<-1, mytype<-1, int, float>, mytype<-1, char, double>>;
using result = mytype<2, mytype<0, int, float>, mytype<1, char, double>>;

// This helper type is used to keep track of the next counter value
template <int c, typename T>
struct type_with_counter {
  static constexpr int counter = c;
  typedef T type;
};

template <typename T> struct assign_ids_helper;

// Base case: we have no mytype and no placeholders to assign, so just give
// back the original type and leave the counter alone.
template <int c, typename T>
struct assign_ids_helper<type_with_counter<c, T>> {
  typedef type_with_counter<c, T> result;
};

// Base case: we have a mytype with no children; assign the placeholder and
// increment the counter.
template <int c, int placeholder>
struct assign_ids_helper<type_with_counter<c, mytype<placeholder>>> {
  typedef type_with_counter<c+1, mytype<c>> result;
};

// Recursive case: one or more children.
template <int c, int placeholder, typename head, typename... tail>
struct assign_ids_helper<type_with_counter<c, mytype<placeholder, head, tail...>>> {
  // Recurse into the first type.
  typedef typename assign_ids_helper<type_with_counter<c, head>>::result head_result;
  // Now use the updated counter to recurse on the tail.
  typedef typename assign_ids_helper<type_with_counter<head_result::counter, mytype<placeholder, tail...>>>::result tail_result;
  // The new type will be given by inserting the head into the tail
  template <typename, typename> struct cons;
  template <int id, typename head_, typename... tail_>
  struct cons<head_, mytype<id, tail_...>> {
    typedef mytype<id, head_, tail_...> result;
  };
  typedef typename cons<typename head_result::type, typename tail_result::type>::result type;
  typedef type_with_counter<tail_result::counter, type> result;
};

template <typename T>
using assign_ids = typename assign_ids_helper<type_with_counter<0, T>>::result::type;

int main() {
  static_assert(std::is_same<assign_ids<type>, result>::value, "");
}

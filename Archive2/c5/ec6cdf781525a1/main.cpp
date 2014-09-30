#include <iostream>
#include <utility>

template <typename T>
struct Field {
  typename T::value_type storage;

  typename T::value_type &operator^(const T &) {
    return storage;
  }
};
template<typename T>
struct tag{using value_type=T;};

static struct:tag<int>{} age;
static struct:tag<std::string>{} last_name;

template<typename... Fields>
struct ctmap_t : public Field<typename std::decay<Fields>::type>... {
};

template<class...Fields>
ctmap_t<Fields...> ctmap( Fields&&... ) { return {}; }


int main() {
  auto person = ctmap( age, last_name );
  person^last_name = "Smith";
  person^age = 104;
}

#include <type_traits>
#include <iostream>

// exemple vector classes
struct vector2
{
  constexpr vector2(unsigned int _x = 0, unsigned int _y = 0) : x(_x), y(_y) {} // for clang

  unsigned int x;
  unsigned int y;
};
struct vector3 : public vector2 // uh ;)
{
  constexpr vector3(unsigned int _x = 0, unsigned int _y = 0, unsigned int _z = 0) : vector2(_x, _y), z(_z) {} // for clang
  unsigned int z;
};

// simple templated generic vector type
// we could make a more generic one, but this would require something like a tuple.
template<unsigned int... Vals>
struct vector
{
    static_assert(!(sizeof...(Vals) + 1), "[...]");
};
template<unsigned int X>
struct vector<X>
{
  using vec_type = unsigned int;
  static constexpr unsigned int value = X;
};

template<unsigned int X, unsigned int Y>
struct vector<X, Y>
{
  using vec_type = vector2;
  static constexpr vector2 value = vector2(X, Y);
};


template<unsigned int X, unsigned int Y, unsigned int Z>
struct vector<X, Y, Z>
{
  using vec_type = vector3;
  static constexpr vector3 value = vector3(X, Y, Z);
};


// a simple wrapper
template<typename V>
struct some_wrapper
{
  static constexpr typename V::vec_type value = V::value;
};


// a dummy function that print something to stdout.
void do_something(int32_t id, const vector3 &value)
{
  std::cout << id << " " << value.z << std::endl;
}
void do_something(int32_t id, const vector2 &value)
{
  std::cout << id << " " << value.y << std::endl;
}
void do_something(int32_t id, int value)
{
  std::cout << id << " " << value << std::endl;
}

// the class used to create the error
template< typename... Args>
class exemple
{
  private:
    // an initialisation that recurse over the Args... template arguments
    template<typename Current, typename... Others>
    void __rec_init() const
    {
      do_something(0, Current::value);
      __rec_init<Others...>();
    }

    // end of recursion
    template<size_t = 0>
    void __rec_init() const {}

    // launch the recursion
    void tpl_init() const
    {
      __rec_init<Args...>();
    }

  public:
    exemple()
    {
      tpl_init();
    }
};

/**************************/
template<typename V>
constexpr typename V::vec_type some_wrapper<V>::value;
/**************************/

int main()
{
  // and here, we get a linker error.
  exemple< some_wrapper<vector<4, 4, 5>>, some_wrapper<vector<4, 1>>, some_wrapper<vector<9>> >();
}
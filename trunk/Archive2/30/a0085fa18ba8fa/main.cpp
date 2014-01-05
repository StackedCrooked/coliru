#define MAGIC(E, ...) \
  enum E { __VA_ARGS__ }; \
  constexpr char const * E ## _string_impl = # __VA_ARGS__

#define MAGIC_STR(E, Offset) \
  std::string (impl::get_start (Offset, E ## _string_impl), impl::get_end (Offset, E ## _string_impl) - impl::get_start (Offset, E ## _string_impl))

namespace impl {
  constexpr char const * get_next (char const * ptr, char needle)
  {
    return *ptr == 0 ? ptr+1 : (*ptr == needle ? ptr+1 : get_next (ptr+1, needle));
  }

  constexpr char const * get_start (int index, char const * ptr, bool first = 1) 
  {
    return index == 0 ? (first ? ptr : ptr+1) : get_start (index-1, get_next (ptr, ','), 0);
  }

  constexpr char const * get_end (int index, char const * ptr)
  {
    return index == 0 ? get_next (ptr, ',')-1 : get_end (index-1, get_next (ptr, ','));
  }
}
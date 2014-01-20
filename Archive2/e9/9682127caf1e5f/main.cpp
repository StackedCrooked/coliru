
template <class T> struct hash;
template <>        struct hash<int> {
    typedef int value_type;
    };

template<class T>
constexpr bool is_defined_hash_type(typename hash<T>::value_type) {
  return true;
}

template<class T>
constexpr bool is_defined_hash_type(T) {
  return false;
}

int main()
{
  static_assert (  is_defined_hash_type< int >(0), "hash<int> should be defined");
  static_assert (! is_defined_hash_type< double>(0), "hash<Enum> should not be defined");
  return 0;
}
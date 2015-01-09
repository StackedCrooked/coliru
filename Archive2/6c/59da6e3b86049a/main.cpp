#include <iostream>

template <typename Base>
struct variant_map {
  template <typename TValue>
  struct Key {
    // TODO
  };

  template <typename TKey, typename TValue>
  void get(TKey key) {
    static_assert(std::is_same<TKey, typename Base::template Key<TValue>>::value,
                  "wrong type passed");
  }

};


struct FruitMap : variant_map<FruitMap> {
  template <typename TValue>
  struct Key : variant_map<FruitMap>::Key<TValue> {};

  static constexpr Key<int> Apple = Key<int>();
  static constexpr Key<double> Orange = Key<double>();
};


int main() {
  
  FruitMap fm;
  fm.get<FruitMap::Key<int>, int>(FruitMap::Apple);

  return 0;
}

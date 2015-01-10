#include <utility>

template <typename Base, template <typename TV> class TKey>
struct VariantMap {
  template <typename ... TKeyValue>
  explicit VariantMap(const TKeyValue& ... key_value_list) {
    static_assert(sizeof...(TKeyValue) % 2 == 0, "Must be an even number of key/value elements");
    InitializeParameters(key_value_list...);
  }
  
 private:
  void InitializeParameters() {}

  template <typename TK, typename TValue, typename ... Rest>
  void InitializeParameters(const TK& key, const TValue& value, const Rest& ... rest) {
    static_assert(
        std::is_same<TK, TKey<TValue>>::value, "The 0th/2nd/4th/etc parameters must be a key");

    const TKey<TValue>& key_refined = key;

    Set(key_refined, value);
    InitializeParameters(rest...);
  }
  
  template <typename TValue>
  void Set(const TKey<TValue>& key, const TValue& value) {
    // Implementation details removed
  }
};

int main() {
    return 0;
}
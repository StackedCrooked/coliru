#include <iostream>
#include <type_traits>
#include <memory>
#include <map>

namespace detail {
  size_t variant_map_key_allocate_counter() {
    static size_t counter = 0;
    counter++;

    return counter;
  }

  struct variant_map_key_raw {
    variant_map_key_raw() : key_counter_(variant_map_key_allocate_counter()) {}

    size_t UniqueId() const {
      return key_counter_;
    }

    virtual void ValueDelete(void* value) const {}

    bool operator<(const variant_map_key_raw& other) const {
      return key_counter_ < other.key_counter_;
    }

   private:
    int key_counter_;
  };
}

/// Variant map implementation

template <typename TValue>
struct variant_map_key : detail::variant_map_key_raw {

  virtual void ValueDelete(void* value) const {
    const std::default_delete<TValue> deleter = std::default_delete<TValue>();
    deleter(reinterpret_cast<TValue*>(value));
  }
};

template <typename Base, template <typename TV> class TKey>
struct variant_map {
  ~variant_map() {
    for (std::pair<const detail::variant_map_key_raw&, void*> kv_pair : storage_map_) {
      // This needs to be virtual since we don't know the compile-time type of the key.
      kv_pair.first.ValueDelete(kv_pair.second);
    }
  }

  template <typename TValue>
  const TValue* get(TKey<TValue> key) const {
    return get_value_ptr(key);
  }

  template <typename TValue>
  TValue* get(TKey<TValue> key) {
    return get_value_ptr(key);
  }

  template <typename TValue>
  bool exists(TKey<TValue> key) const {
    return get_value_ptr<TValue>(key) != nullptr;
  }

  template <typename TValue>
  void set(TKey<TValue> key, const TValue& value) {
    TValue* previous_value = get(key);
    key.ValueDelete(previous_value);

    storage_map_[key] = new TValue(value);
  }

 private:
  template <typename TValue>
  TValue* get_value_ptr(TKey<TValue> key) {
    return reinterpret_cast<TValue*>(storage_map_[key]);
  }

  template <typename TValue>
  const TValue* get_value_ptr(TKey<TValue> key) const {
    return reinterpret_cast<const TValue*>(storage_map_[key]);
  }

  // Map the key ID to the raw storage.
  std::map<detail::variant_map_key_raw, void*> storage_map_;
};


/// How another class uses a variant map by defining its own keys

template <typename TValue>
struct FruitMapKey : variant_map_key<TValue> {
  FruitMapKey() {} // Don't like how I'm forced to make a default constructor
};

struct FruitMap : variant_map<FruitMap, FruitMapKey> {
  template <typename TValue>
  using Key = FruitMapKey<TValue>;

  static const Key<int> Apple;
  static const Key<double> Orange;
};

// Don't like how this has to repeat itself <>
const FruitMap::Key<int> FruitMap::Apple;
const FruitMap::Key<double> FruitMap::Orange;

////////////////////
////////////////////
////////////////////

int main() {
  
  FruitMap fm;
  int* apple = fm.get(FruitMap::Apple);
  std::cout << "apple ptr is " << apple << "\n";
  fm.set(FruitMap::Orange, 1.5);

  double* orange = fm.get(FruitMap::Orange);
  std::cout << "orange ptr is " << orange << "\n";
  std::cout << "orange value is " << *orange << "\n";


  return 0;
}

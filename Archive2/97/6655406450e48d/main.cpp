#include <iostream>

template <typename Base>
struct VariantMap
{
    template <typename TValue>
    struct Key {};
    
    template <typename TValue>
    TValue& get(Base::Key<typename TValue> base_key) {
        // TODO: impl
        return TValue();
    }
};

struct FruitMap : VariantMap<FruitMap> {
    template <typename T>
    struct Key : VariantMap<FruitMap>::Key<T> {};
    
    Key<int> Apple;
    Key<double> Orange;
};


int main() {
  FruitMap f;
  
  int apple_value = f.get(FruitMap.Apple);
  
  return 0;
}

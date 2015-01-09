template <typename TValue>
struct FruitMapKey : variant_map_key<TValue> {
  FruitMapKey() {}
};

struct FruitMap : variant_map<FruitMap, FruitMapKey> {
  template <typename TValue>
  using Key = FruitMapKey<TValue>;

  static const Key<int> Apple;
  static const Key<double> Orange;
};

const FruitMap::Key<int> FruitMap::Apple;
const FruitMap::Key<double> FruitMap::Orange;

int main()
  FruitMap fm;
  int* apple = fm.get(FruitMap::Apple);
  std::cout << "apple ptr is " << apple << "\n";
  fm.set(FruitMap::Orange, 1.5);

  double* orange = fm.get(FruitMap::Orange);
  std::cout << "orange ptr is " << orange << "\n";
  std::cout << "orange value is " << *orange << "\n";

  return 0l
}
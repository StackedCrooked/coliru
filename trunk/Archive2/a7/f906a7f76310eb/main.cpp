#include <type_traits>
#include <utility>
#include <memory>

class Device {
public:
  virtual Device * Clone() const {
    return new Device(*this);
  }
};

class Radar : public Device {
public:
  virtual Radar * Clone() const override {
    return new Radar(*this);
  }
};

// Clone factories

template <typename Class, typename T>
std::unique_ptr<Class> clone_unique(T&& source)
{
  static_assert(std::is_base_of<Class, typename std::decay<decltype(*source)>::type>::value,
    "can only clone for pointers to the target type (or base thereof)");
  return std::unique_ptr<Class>(source->Clone());
}

int main()
{
  std::unique_ptr<Radar> radar(new Radar());
  std::unique_ptr<Device> cloned = clone_unique<Device>(radar);
}

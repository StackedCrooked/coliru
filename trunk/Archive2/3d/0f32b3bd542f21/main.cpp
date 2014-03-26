#include <array>
#include <memory>

class Object
{};

int main()
{
  std::array<std::unique_ptr<Object>, 4> p_object;
}
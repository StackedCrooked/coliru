#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

template<typename T>
static
std::pair< std::vector<T>, std::vector<T> >
compare(std::vector<T>& old_user_devices,
        std::vector<T>& new_user_devices)
{
  std::sort(std::begin(old_user_devices), std::end(old_user_devices));
  std::sort(std::begin(new_user_devices), std::end(new_user_devices));

  std::vector<T> plus(new_user_devices.size());
  std::vector<T> minus(old_user_devices.size());

  {
    auto it = std::set_difference(
      std::begin(old_user_devices),
      std::end(old_user_devices),
      std::begin(new_user_devices),
      std::end(new_user_devices),
      std::begin(minus));

    minus.resize(it - minus.begin());
  }

  {
    auto it = std::set_difference(
      std::begin(new_user_devices),
      std::end(new_user_devices),
      std::begin(old_user_devices),
      std::end(old_user_devices),
      std::begin(plus));

    plus.resize(it - plus.begin());
  }

  return {std::move(plus), std::move(minus)};
}

template <typename T>
void
display(std::string const& name, std::vector<T> const& to_display)
{
  std::cerr << name << "(" << to_display.size() << "):" << std::endl;
  std::for_each(to_display.begin(), to_display.end(), [] (T const& i)
                { std::cerr << "- " << i << std::endl; });

}

int main()
{

  {
    std::vector<int> old_{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> new_{2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16};

    auto ret = compare(old_, new_);

    display("Removed", ret.second);
    display("Added", ret.first);
  }
  std::cerr << std::string(30, '-') << std::endl;
  {
    std::vector<int> old_{};
    std::vector<int> new_{2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16};

    auto ret = compare(old_, new_);

    display("Removed", ret.second);
    display("Added", ret.first);
  }
  std::cerr << std::string(30, '-') << std::endl;
  {
    std::vector<int> old_{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> new_{};

    auto ret = compare(old_, new_);

    display("Removed", ret.second);
    display("Added", ret.first);
  }
}
#include <string>
#include <iostream>
#include <type_traits>
#include <typeinfo>

struct EuronextGroup
{
  std::string criteria_;
  const std::string& get_criteria() const { return criteria_; }
  int active;
  int get_active() const { return active; }
};

struct Group
{
  std::string criteria_;
  const std::string& get_criteria() const { return criteria_; }
};


////////////////////////////////////////////////////////////////////////////////
template <typename T, typename Enabled = void>
struct add_active : public std::false_type
{
};

template <typename T>
struct add_active<T, typename std::enable_if<std::is_member_function_pointer<decltype(&T::get_active)>::value>::type> :
  public std::true_type
{
};


template <typename T>
void external_check(const T& group)
{
  std::cout << group.get_criteria();
  if (add_active<T>::value)
    std::cout << " has_active";
  std::cout << std::endl;
}

////////////////////////////////////////////////////////////////////////////////
int main()
{
  EuronextGroup eg { "EuronextGroup", 42 };
  Group g { "Group" };
  external_check(eg);
  external_check(g);
  return 0;
}

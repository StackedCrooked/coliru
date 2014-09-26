#include <string>
#include <iostream>
#include <set>
#include <initializer_list>
#include <algorithm>

template<typename T, typename T2>
bool contains(T const& value, std::initializer_list<T2> const& set)
{
  return std::find(std::begin(set), std::end(set), value) != std::end(set);
}

int main(void)
{
  std::set<std::wstring> values = { L"bar", L"not" };

  for (std::wstring val : values) {
    std::wcout << "\"" << val << "\" ";
    if (contains(val, { L"foo", L"bar", L"baz", L"doom" })) {
      std::wcout << "found" << std::endl;
    }
    else {
      std::wcout << "not found" << std::endl;
    }
  }
}
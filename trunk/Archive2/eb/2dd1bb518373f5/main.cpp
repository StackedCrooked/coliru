#include <locale>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>

template <typename Int = std::uint8_t,
  typename Char = char,
  typename Traits = std::char_traits<Char>,
  typename Allocate = std::allocator<Char>,
  typename Locale = std::locale>
std::vector<Int> basic_convert(std::basic_string<Char, Traits, Allocate> const& src, Locale locale = Locale())
{
  using string_type = std::basic_string<Char, Traits, Allocate>;

  auto ishex = [&locale] (decltype(*src.begin()) c) {
      return std::isxdigit(c, locale); };

  if ((src.length() % 2) != 0) {
    throw std::invalid_argument("conversion error: input is not even length");
  }

  if (!std::all_of(std::begin(src), std::end(src), ishex)) {
    throw std::invalid_argument("conversion error: input values are not not all xdigits");
  }

  std::vector<Int> result(src.length() / 2, 0);

  auto str = std::begin(src);
  std::for_each(std::begin(result), std::end(result), [&str](decltype(*std::begin(result))& element) {
    element = static_cast<Int>(std::stoul(string_type(str, str + 2), nullptr, 16));
    std::advance(str, 2);
  });

  return result;
}

std::vector<std::uint8_t> convert(std::string const& src)
{
  return basic_convert<std::uint8_t>(src, std::locale());
}

#include <iostream>
#include <iomanip>

int main()
{
  using namespace std;
  try {
    auto result = convert("123");
  }
  catch (exception& e) {
    cout << "Expected length error: " << e.what() << endl;
  }
  try {
    auto result = convert("zxcv");
  }
  catch (exception& e) {
    cout << "Expected data error: " << e.what() << endl;
  }
  try {
    auto result = convert("00112233445566778899AaBbCcDdEeFf");
    cout << hex;
    for (auto&& i : result) {
      cout << +i << " ";
    }
    cout << endl;
  }
  catch (exception& e) {
    cout << "Unexpected: " << e.what() << endl;
  }
}

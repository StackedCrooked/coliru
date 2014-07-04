#include <locale>
#include <codecvt>
#include <iostream>

template <typename Facet>
struct usable_facet : Facet {
  using Facet::Facet;
};

using codecvt = usable_facet<std::codecvt_byname<wchar_t, char, std::mbstate_t>>;

int main() {
  std::wstring_convert<codecvt> convert(new codecvt("en_US.UTF-8")); // platform specific locale strings

  std::wstring w = convert.from_bytes("\u00C0");
  
  std::wcout.imbue(std::locale(std::locale(), new codecvt("en_US.UTF-8")));
  std::wcout << w << '\n';
}

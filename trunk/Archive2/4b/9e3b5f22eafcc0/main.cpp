#include <iostream>
#include <string>

template <class charT>
  struct js_traits { };

template <> struct js_traits<char> {
  static constexpr char txt_f() { return '\f'; }
  /// ..
};

template <> struct js_traits<wchar_t> {
  static constexpr wchar_t txt_f() { return L'\f'; }
  /// ..
};

template<class wcharT>
void test(const wcharT* s) {
    while(*s) {
     switch (*s) {
       case js_traits<wcharT>::txt_f():
       std::cout << "<f>";
       break;
       default:
       std::cout << *s;
     };       
     s++;
    } 
}

int main()
{
   test("test\f");
   std::cout << std::endl;
   test(L"test\f");
   std::cout << std::endl;
}

#include <iostream>
#include <codecvt>
int main() {
  std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv_out(std::cout.rdbuf());
  std::wostream out(&conv_out);
  out << L"双喜雙喜!" << std::endl;
}
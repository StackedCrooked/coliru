#include <iostream>
 
int main() {
  std::wcout.sync_with_stdio(false);
  std::wcout.imbue(std::locale("en_US.utf8"));
  std::wcout << L"双喜雙喜!" << std::endl;
}
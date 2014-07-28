#include <cstdio>
#include <cwchar>

int main()
{
  std::printf("NULL pointer is %p\n", nullptr);
  std::wprintf(L"NULL pointer is %p\n", nullptr);
}

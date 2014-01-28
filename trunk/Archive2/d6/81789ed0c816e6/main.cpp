#include <stdio.h>
constexpr inline size_t strlen_constexpr(const char* baseChar) {
    return (
            ( baseChar[0] == 0 )
            ?(// if {
              0
              )// }
            :(// else {
              strlen_constexpr( baseChar+1 ) + 1 
              )// }
            );
}

int main()
{
  printf("%d\n", strlen_constexpr("Hello World!\n"));
}
#include <iostream>
#define foo(x) C_ ## x

enum Test
{
        C_TX_MAC = 0x0100, // Pre-Processor should replace C_TX_ to TX_
        C_RX_MAC = 0x0101  // But Not Working.
};

int main()
{
   std::cout << foo(TX_MAC) << ' ' << foo(RX_MAC) << '\n';
}
#include <cstdint>
using std::uint8_t;

volatile uint8_t* array[16];

void processArray(const volatile uint8_t**)
{
}

int main()
{
     processArray(array);
}

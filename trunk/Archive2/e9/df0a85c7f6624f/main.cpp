#include <iostream>
#include <time.h>

int main()
{
    srand(time(NULL));
    int number1, number2;
    for (int i = 0; i < 25; ++i) {
      number1 = rand() % 3;
      number2 = rand() % 3;

      printf("%i, %i\n", number1, number2);
    }
    return 0;
}
#include <iostream>

template<class T, T... Firsts, class... TSecond>
void LetsStart(TSecond... Seconds) {
   int _[] = { 0, (void(std::cout << Firsts << " " << Seconds << "\n"), 0)... };
   (void)_;
}

int main()
{
    LetsStart<int, 1, 2, 3>("4", "5", "6");
}
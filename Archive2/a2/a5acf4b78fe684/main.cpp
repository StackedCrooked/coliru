#include <iostream>
#include <chrono>

using namespace std::chrono;

bool UInt32ToPaddedString(uint32_t number, uint32_t maxDigits, char* buff, uint32_t buffSize)
{
    static const char DIGITS[] =
    "0001020304050607080910111213141516171819"
    "2021222324252627282930313233343536373839"
    "4041424344454647484950515253545556575859"
    "6061626364656667686970717273747576777879"
    "8081828384858687888990919293949596979899";

	if (buffSize < maxDigits + 1) 
		return false;

	char *buffer_end = buff + maxDigits;
    while (number >= 100) {
      // Integer division is slow so do it for a group of two digits instead
      // of for every digit. The idea comes from the talk by Alexandrescu
      // "Three Optimization Tips for C++". See speed-test for a comparison.
      unsigned index = (number % 100) * 2;
      number /= 100;
      *--buffer_end = DIGITS[index + 1];
      *--buffer_end = DIGITS[index];
    }
    if (number < 10) {
      *--buffer_end = static_cast<char>('0' + number);
    }
	else {
		unsigned index = static_cast<unsigned>(number * 2);
		*--buffer_end = DIGITS[index + 1];
		*--buffer_end = DIGITS[index];
	}
	while (buffer_end > buff) *--buffer_end = '0';
    return true;
}

int main(int argc, char* argv[])
{
	char buff[10] = {0};

	high_resolution_clock::time_point time1 = high_resolution_clock::now();
	uint32_t sh = 1;
	for (uint32_t i = 1000; i <= 10001000 /*10M*/; i++)
	{
		UInt32ToPaddedString(i, 8, buff, 10);
		if (i > sh)
		{
			std::cout << i << ": " << buff << std::endl;
			sh <<= 1;
		}
	}
	high_resolution_clock::time_point time2 = high_resolution_clock::now();
	uint64_t time = duration_cast<microseconds>(time2 - time1).count();
	std::cout << "\nUInt32ToPaddedString:\n\n" << time << " microsecond(s) to run 10M times\n";
   std::cout << "or " << duration_cast<nanoseconds>(time2 - time1).count()/10000000 << " nanosecond(s) to run once\n";

   std::cout << "\nThat's all, folks!" << std::endl;
	return 0;
}

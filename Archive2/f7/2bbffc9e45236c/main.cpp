#include <iostream>
#include <chrono>

using namespace std::chrono;

bool UInt32ToPaddedString(uint32_t number, uint32_t maxDigits, char* buff, uint32_t buffSize)
{
       buff[maxDigits] = 0;
 
       do
       {
              int digit;
              if(buffSize == 0 || maxDigits == 0)
                     return false;
              digit = number % 10;
              buff[--maxDigits] = digit + '0';
              --buffSize;
              //number /= 10;
              number = (uint32_t)(number * 0.1);
       } while(number > 0);
 
       if(buffSize == 0)
              return false;
 
       while(maxDigits > 0)
              buff[--maxDigits] = '0';
 
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

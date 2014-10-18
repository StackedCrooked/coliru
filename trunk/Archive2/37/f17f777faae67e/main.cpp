#include <iostream>
#include <map>

using namespace std;

int main()
{
    int numbers[] = {1,2,3,4,5,6,7,5,5,6,1,5,5,8,9};
    std::map<int, int> num_counter;
    for(int i = 0; i < 15; ++i) // 15 is an array's size
        num_counter[numbers[i]]++;
    int number = 0;
    int numbrq = 0;
    for(std::map<int, int>::iterator it = num_counter.begin(); it != num_counter.end(); ++it)
    {
        if (it -> second > numbrq)
        {
            number = it -> first;
            numbrq = it -> second;
        }
    }
    std::cout << "Mode number " << number << " occurs " << numbrq << " times" << std::endl;
}

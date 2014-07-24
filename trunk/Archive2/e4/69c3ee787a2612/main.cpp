#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> convert(int number)
{
    std::vector<int> result;

	if (number == 0) {
		result.push_back(0);
	}

	while (number) {
		int temp = number % 10;
        number /= 10;
		result.push_back(temp);
        //result.insert(result.begin(), temp); // alternative... inserts in "forward" order
	}

    // push_back inserts the elements in reverse order, so we reverse them again
	std::reverse(result.begin(), result.end());
    
    return result;
}

int main()
{
    int i = 123;
    auto result = convert(i);
    std::cout << i << std::endl;
    for (auto& j : result) {
        std::cout << j << ',';
    }
    std::cout << std::endl;
}
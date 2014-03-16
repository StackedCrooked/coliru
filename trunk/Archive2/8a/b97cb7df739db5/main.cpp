#include <iostream>
#include <algorithm>
#include <initializer_list>

double average(const std::initializer_list<double> &list) {
    
    double sum = std::accumulate(list.begin(), list.end(), 0.0);
    return sum / list.size();
}

int main()
{
    double number1, number2, number3, number4;
    std::cout << "Enter four numbers: ";
	std::cin >> number1 >> number2 >> number3 >> number4;
    
    //Display result
    std::cout << "The average of " << number1 << ", " << number2
	     << ", " << number3 << " and " << number4 << " is: "
         << average({number1, number2, number3, number4})
	     << std::endl;
    
    return 0;
}
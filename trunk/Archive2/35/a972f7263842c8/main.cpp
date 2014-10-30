#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ctype.h>

template<typename T>
class vectorVerEin
{
public:
    void push_back(T value)
	{
		v.push_back(value);
		sort();
	}
	bool empty()
	{
		return v.empty();
	}
	int size()
	{
		return v.size();
	}

	void print()
	{
		for (std::vector<int>::iterator it1 = v.begin(); it1 < v.end(); it1++)
		{
			std::cout << *it1 << "\n";
		}
	}

private:
	
	void sort()
	{
		std::sort(v.begin(), v.end());
	}

	std::vector<T> v;
};

std::string transformIntToString(int value) { return std::to_string(value); }
void transformToUpper(char& value) { value = toupper(value); }
bool isEven(int value) { return 0 == value % 2; }
bool isOdd(int value) { return !isEven(value); }
void exer1();
void exer2();
void exer3();
void exer4();
void exer5();
void exer6();

int main()
{
	exer1();
	exer2();
	exer3();
	exer4();
	exer5();
	exer6();
}

// 1. Write a code which will be able to transform vector of int to vector of strings. 
// Hint: integer type can be converted to string by std::to_string() function.
void exer1()
{
	std::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	std::vector<std::string> vs;
	vs.resize(v.size());
	std::transform(v.begin(), v.end(), vs.begin(), transformIntToString);

	std::cout << "exer 1 done\n";
}

// 2. Write a code which will change string "example" to uppercase (use std::for_each and std::toupper).
void exer2()
{
	std::string sample = "example";

	std::cout << "before:" << sample << "\n";
	std::for_each(sample.begin(), sample.end(), transformToUpper);
	std::cout << "after:" << sample << "\n";
	std::cout << "exer 2 done\n";
}

//3. Write a code which will count even values from vector of ints std::vector<int> v = {1, 5, 16, 2, 7, 1044, 236, 19, 99};
void exer3()
{
	std::vector<int> v = { 1, 5, 16, 2, 7, 1044, 236, 19, 99 };

	int count = std::count_if(v.begin(), v.end(), isEven);

	std::cout << count << "\n";
	std::cout << "exer3 done\n";
}

//4. Write a code which will get minimum and maximum value from vector std::vector<int> v = {1, 5, 16, 2, 7, 1044, 236, 19, 99};
void exer4()
{
	std::vector<int> v = { 1, 5, 16, 2, 7, 1044, 236, 19, 99 };
	std::vector<int>::const_iterator min_it = std::min_element(v.begin(), v.end());
	std::vector<int>::const_iterator max_it = std::max_element(v.begin(), v.end());

	std::cout << "Minimum: " << *min_it << "\n";
	std::cout << "Maximum: " << *max_it << "\n";
	std::cout << "exer4 done\n";
}

//5. Write a code which will remove all of odd values from vector std::vector<int> v = {1, 5, 16, 2, 7, 1044, 236, 19, 99};
void exer5()
{
	std::vector<int> v = { 1, 5, 16, 2, 7, 1044, 236, 19, 99 };

	std::vector<int>::iterator it = std::remove_if(v.begin(), v.end(), isOdd);
	v.erase(it, v.end());

	std::cout << "exer5 done\n";
}

//6. Write your own adaptation of std::vector which will sort elements (you can use std::sort()) after push_back and also provide interface with empty() and size() methods.
void exer6()
{
	vectorVerEin<int> v;
	v.push_back(10);
	v.push_back(99);
	v.push_back(5);
	v.push_back(1);
	v.push_back(1000);
	v.push_back(77);

	std::cout << "Empty: " << v.empty() << "\n";
	std::cout << "Size: " << v.size() << "\n";

	v.print();
	std::cout << "exer6 done\n";
}
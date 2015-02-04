#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <functional>

struct isEven
{
    typedef int argument_type;
    bool operator () (const argument_type & x) const
    {
        return x%2 == 0;
    }
};

void makeUpperCase(char &c)
{
    c = std::toupper(c);
}

std::string decrypt(int value)
{
    return std::to_string(value);
}

template <typename T>
T getMax(std::vector<T> vec)
{
    T largest = vec[0];
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if(*it > largest)
            largest = *it;
    }
    return largest;
}

template <typename T>
T getMin(std::vector<T> vec)
{
    T smallest = vec[0];
    for(std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if(*it < smallest)
            smallest = *it;
    }
    return smallest;
}

void exercise1();
void exercise2();
void exercise3();
void exercise4();
void exercise5();
void exercise7();

int main()
{
    exercise1();
    exercise2();
    exercise3();
    exercise4();
    exercise5();
    exercise7();
    return 0;
}

void exercise1()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);

    for(auto const& val : exercise)
        std::cout << val;
        
    std::cout << " String: ";
    std::vector<std::string> s;
    std::transform(exercise.begin(), exercise.end(), std::back_inserter(s), decrypt);
    
    std::string a;
    for(auto const& c : s)
        a += c;    
    std::cout << a << std::endl;
}

void exercise2()
{
    std::string s = "example";
    std::for_each(s.begin(), s.end(), makeUpperCase);
    std::cout << s << std::endl;
}

void exercise3()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);

    int count = std::count_if(exercise.begin(), exercise.end(), isEven());
    std::cout << count << std::endl;
}

void exercise4()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);
    
    std::vector<int>::const_iterator minIt = std::min_element(exercise.begin(), exercise.end());
    std::vector<int>::const_iterator maxIt = std::max_element(exercise.begin(), exercise.end());
    
    std::cout << "Min: " << *minIt << ", Max:" << *maxIt << std::endl;
    
    std::cout << "Using template function getMax: " << getMax(exercise);
    std::cout << " ,getMin:" << getMin(exercise) << std::endl;
}

void exercise5()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);
    
    std::vector<int>::const_iterator it = std::remove_if(exercise.begin(), exercise.end(), std::not1(isEven()));
    exercise.erase(it, exercise.end());
    
    for(auto const& val : exercise)
        std::cout << val;
}

void exercise7()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);
    
    std::set<int> uniqueVals(exercise.begin(), exercise.end());
    
    std::cout << std::endl;
    for(auto const & val : uniqueVals)
        std::cout << val;
}
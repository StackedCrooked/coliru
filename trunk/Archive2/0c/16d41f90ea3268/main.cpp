#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <set>

void makeUpper(char& value) {value = toupper(value);}

char decrypt (int value) {return static_cast<char> (value+=48);}

//bool isEven (int value) {if ((value%2)==0)return true; return false;}
struct isEven {
  bool operator() (const int& value) const {if ((value%2)==0)return true; return false;}
  typedef int argument_type;
};

    
    

int main()
{
   
std::vector<int> exercise;
exercise.push_back(1);
exercise.push_back(2);
exercise.push_back(3);
exercise.push_back(2);
exercise.push_back(1);
exercise.push_back(4);
exercise.push_back(5);
   


std::cout<<"1. Write a code which will be able to transform a vector of int to vector of strings"<< std::endl;
std::string s ;
std::transform(exercise.begin(), exercise.end(), std::back_inserter(s), decrypt);
std::cout << s << std::endl <<std::endl;


std::cout<< "2. Write a code which will change string example to uppercase (use std::for each)" <<std::endl;
std::string ex = "example";
std::cout << "Before : " << ex <<std::endl;
std::for_each(ex.begin(), ex.end(), makeUpper);
std::cout << "After  : " << ex <<std::endl <<std::endl;

std::cout<< "3. Write a code which will count even values from vector of ints"<<std::endl;
int count = std::count_if(exercise.begin(), exercise.end(), isEven());
std::cout<< "Number of even numbers: " << count << std::endl <<std::endl;


std::cout<< "4. Write a code which will get minimum and maximum value from vector"<<std::endl;
std::vector<int>::const_iterator min_it = std::min_element(exercise.begin(), exercise.end());
std::vector<int>::const_iterator max_it = std::max_element(exercise.begin(), exercise.end());
std::cout<< "Min: " << *min_it << " Max: " << *max_it << std::endl <<std::endl<<std::endl;

std::cout<< "5.Write a code which will remove all odd values from vector" <<std::endl;
std::cout<< "Before : ";
std::copy(exercise.begin(), exercise.end(), std::ostream_iterator<int>(std::cout, " "));
std::cout<<std::endl;
std::vector<int>::iterator remove_it = std::remove_if(exercise.begin(), exercise.end(), std::not1(isEven()));
exercise.erase(remove_it, exercise.end());
std::cout<< "After :  ";
std::copy(exercise.begin(), exercise.end(), std::ostream_iterator<int>(std::cout, " "));
std::cout<<std::endl<< std::endl;

std::cout<< "7. Write a code that will get all unique values from the vector ( least lines => best)"<<std::endl;
std::vector<int> exer;
exer.push_back(1);
exer.push_back(2);
exer.push_back(3);
exer.push_back(2);
exer.push_back(1);
exer.push_back(4);
exer.push_back(5);
std::cout<< "Before : ";
std::copy(exer.begin(), exer.end(), std::ostream_iterator<int>(std::cout, " "));
std::cout<<std::endl;
std::set<int> copy(exer.begin(), exer.end());
std::cout<< "After : ";
std::copy(copy.begin(), copy.end(), std::ostream_iterator<int>(std::cout, " "));
std::cout<<std::endl;
}



#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <functional>
#include <set>

//char decrypt(int value) {return static_cast<char>((value / 100)^0x16);}

std::string convert2String(int val){return std::to_string(val);}

void exer1()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);
    
    std::vector<std::string> output;
    output.resize(exercise.size());
    std::transform(exercise.begin(), exercise.end(), output.begin(), convert2String);
    
    std::copy(output.begin(), output.end(), std::ostream_iterator<std::string>(std::cout, " "));
}

void toUpperCase(char& letter){letter = toupper(letter);}

void exer2()
{
    std::string ex("example");
    std::for_each(ex.begin(), ex.end(), toUpperCase);
    std::cout << std::endl << ex << std::endl;
}

bool evenNum(int num)
{
   return (num%2) == 0;
}

void exer3()
{
   std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);
    
    int counter = std::count_if(exercise.begin(), exercise.end(), evenNum);
    std::cout << counter << std::endl;
}

void exer4()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);    
    
    std::cout << "MIN: " << *(std::min_element(exercise.begin(), exercise.end()));
    std::cout << " MAX: " << *(std::max_element(exercise.begin(), exercise.end())) << std::endl;
}

bool oddNum(int num)
{
   return (num%2) != 0;
}

void exer5()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);
    
    std::vector<int>::iterator it = std::remove_if(exercise.begin(),exercise.end(), oddNum);
    exercise.erase(it, exercise.end());
    
    std::copy(exercise.begin(), exercise.end(), std::ostream_iterator<int>(std::cout, " "));
}



void exer7()
{
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);
    
    std::set<int> copier(exercise.begin(), exercise.end());
    std::cout << std::endl;
    std::copy(copier.begin(), copier.end(), std::ostream_iterator<int>(std::cout, " "));    
}    

int main()
{       
     exer1();
     exer2();
     exer3();
     exer4();
     exer5();
     exer7();
}









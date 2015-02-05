#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<iterator>
#include<locale>
#include<functional>
#include<sstream>

bool isEven(int value)  { return (value%2==0); }

std::string toStr(int value) {
    std::stringstream ss;
    ss<<value;
    return ss.str();
    }

void toUp(char &letter)  {
    letter = toupper(letter);
}

int main()  {
    std::vector<int> exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);
    exercise.push_back(4);
    exercise.push_back(5);



//    Exercise #1
//    Write a code which will be able to transform vector of int to vector of strings.

    std::vector<std::string> exerStr;
    exerStr.resize(exercise.size());
    std::transform(exercise.begin(), exercise.end(), exerStr.begin(), toStr);

    std::cout<<"Exercise #1"<<std::endl;
    std::copy(exerStr.begin(), exerStr.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cout<<std::endl;

//  Exercise #2
//    Write a code which will change string "example" to uppercase (use std::for_each).

    std::string s = "example";
    std::for_each(s.begin(), s.end(), toUp);

    std::cout<<std::endl<<"Exercise #2"<<std::endl;
    std::cout<<s<<std::endl;

//  Exercise #3
//    Write a code which will count even values from vector of ints

    int countEven = std::count_if(exercise.begin(), exercise.end(), isEven);

    std::cout<<std::endl<<"Exercise #3"<<std::endl;
    std::cout<<countEven<<std::endl;

//   Exercise #4
//    Write a code which will get minimum and maximum value from vector

    std::vector<int>::iterator minValue = std::min_element(exercise.begin(), exercise.end());
    std::vector<int>::iterator maxValue = std::max_element(exercise.begin(), exercise.end());

    std::cout<<std::endl<<"Exercise #4"<<std::endl;
    std::cout<<*minValue<<std::endl;
    std::cout<<*maxValue<<std::endl;

//  Exercise #5
//    Write a code which will remove all of odd values from vector
    std::vector<int> exerCopy;
    exerCopy.resize(exercise.size());
    std::copy(exercise.begin(), exercise.end(), exerCopy.begin());

    std::vector<int>::iterator end = std::remove_if(exerCopy.begin(), exerCopy.end(), std::not1(std::ptr_fun(isEven)));
    exerCopy.erase(end, exerCopy.end());

    std::cout<<std::endl<<"Exercise #5"<<std::endl;
    std::copy(exerCopy.begin(), exerCopy.end(), std::ostream_iterator<int>(std::cout, "\n"));


//    Exercise #6
//    Write a code that will get all unique values from the vector (least lines => best answer)

    std::vector<int> uniqueVals;
    for(std::vector<int>::iterator it = exercise.begin(); it!=exercise.end(); ++it)   {
        if (std::count(exercise.begin(), exercise.end(), *it)==1)        uniqueVals.push_back(*it);
    }

    std::cout<<std::endl<<"Exercise #6"<<std::endl;
    std::copy(uniqueVals.begin(), uniqueVals.end(), std::ostream_iterator<int>(std::cout, "\n"));

}
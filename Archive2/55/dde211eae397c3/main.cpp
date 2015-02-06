#include<set>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<iterator>

std::string TransformToString(int value)
{
    return std::to_string(value);
}

struct isEven
{
    bool operator()(const int& value) const {return value % 2 == 0;}
    typedef int argument_type;
};
void ConvertToCaps(char &c)
{
    c = c -32;
}

void OutputValue(int val)
{
    std::cout<<val<<" ";
}

class Max
{
public:
    Max(){};
    void operator()(int& val){
        if(val > max) { this->max = val; }
    }
    int getMax() { return max; }
private:
    int max;
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
	
	//1. Write a code which will be able to transform vector of int to vector of strings
	std::vector<std::string> vectorString;
	std::transform(exercise.begin(), exercise.end(), std::back_inserter(vectorString), TransformToString);
    std::copy(vectorString.begin(), vectorString.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout<<std::endl;    

	//2. Write a code which will change string "example" to uppercase (use std::for_each)
	std::string str = "example";
	std::for_each(str.begin(), str.end(), ConvertToCaps);
    std::cout<<str;

//3. Write a code which will count even values from vector of ints
	std::vector<int> vectorInts;
	vectorInts.push_back(10);
	vectorInts.push_back(25);
	vectorInts.push_back(31);
	vectorInts.push_back(20);
	vectorInts.push_back(333);
	vectorInts.push_back(444);
	vectorInts.push_back(5);

	int count = std::count_if(vectorInts.begin(), vectorInts.end(), isEven());
	std::cout << std::endl << count <<std::endl;

	//4. Write a code which will get minimum and maximum value from vector.
    std::vector<int>::const_iterator it = std::min_element(vectorInts.begin(), vectorInts.end());
    std::cout<<"min: "<<*it<<std::endl;
    
     std::vector<int>::const_iterator it1 = std::max_element(vectorInts.begin(), vectorInts.end());
    std::cout<<"max: "<<*it1<<std::endl;
    
	//5. Write a code which will remove all of odd values from vector.
    
    std::vector<int>::iterator it2 = std::remove_if(vectorInts.begin(), vectorInts.end(), std::not1(isEven()));
    vectorInts.erase(it2, vectorInts.end());
    std::for_each(vectorInts.begin(), vectorInts.end(), OutputValue);
    
	//6. Write a code that will get all unique values from the vector(least line => best answer)
    std::vector<int> vectorInts2;
    vectorInts2.push_back(5);
	vectorInts2.push_back(5);
	vectorInts2.push_back(3);
	vectorInts2.push_back(2);
	vectorInts2.push_back(6);
	vectorInts2.push_back(3);
	vectorInts2.push_back(7);
   
    std::set<int> setInt;
    std::cout<<std::endl<<"Unique Values: ";
    setInt.insert(vectorInts2.begin(), vectorInts2.end());
    for(std::set<int>::const_iterator it4 = setInt.begin(); it4 != setInt.end(); ++it4)
    {std::cout << " " << *it4;}
    
	//7. http://bit.ly/1zBfYnc

    return 0;
}
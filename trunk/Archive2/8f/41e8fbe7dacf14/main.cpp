#include <iostream>
#include <string>
#include<vector>
#include<algorithm>
#include<set>
#include <sstream>




std::string trans(int value) {
    //return static_cast<char>((value) ^ 0x16);
   // char valuestr;
    return std::to_string(value);
    }
    
void makeUpper(char& value) { value = toupper(value);}

bool isOdd(int & value){
    
    if ((value%2)==1)
        return true;
    else 
        //container.erase(value);
        
        return false;
    
    }


bool numbers(int & value){ 
    
    if ((value%2)==0)
        return true;
    else 
        //container.erase(value);
        
        return false;

}


int main(){
    
    std::vector<int>exercise;
    exercise.push_back(1);
    exercise.push_back(2);
    exercise.push_back(3);
    exercise.push_back(2);
    exercise.push_back(1);  
    exercise.push_back(4);
    exercise.push_back(5);
    
    //============================== Q1===========
    
    std::vector<std::string>catcher;
    std::transform(exercise.begin(), exercise.end(), std::back_inserter(catcher), trans);
     for(auto const& val: catcher)
    {
        std::cout << val;
    }
    //=========================================
    
    std::cout <<std::endl;

    //=======================to uppercase==================
    std::string name = "example";
    
    std::for_each(name.begin(), name.end(), makeUpper);
    
    std::cout<<name<<std::endl;
    //========================================
    
    //count even
    int count = std::count_if(exercise.begin(), exercise.end(), numbers);  
    std::cout<<count<<std::endl;
    
    
    //======================================remove number
   
    std::set<int> get(exercise.begin(), exercise.end());

    for(auto const& val: get)
    {
        std::cout << val;
    }

     std::cout <<std::endl;
    
    //========================================== remove odd========
    
    std::vector<int>::iterator it = std::remove_if(exercise.begin(), exercise.end(), isOdd);
    exercise.erase(it, exercise.end());
    
     for(auto const& val: exercise)
    {
        std::cout << val;
    }

     std::cout <<std::endl;
    
    std::vector<int>::iterator min = std::min_element(exercise.begin(), exercise.end());
    std::cout<<"The minimum value is "<<*min<<std::endl;
    
    std::vector<int>::iterator max = std::max_element(exercise.begin(), exercise.end());
    std::cout<<"The maximun value is "<<*max<<std::endl;
    


    
    
     
    
    
    }
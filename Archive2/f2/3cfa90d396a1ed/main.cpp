#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>
#include <set>

std::string to_str(int value){ 
    return std::to_string(value);
}

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

    //1
    std::vector<std::string> s;
    s.resize(exercise.size());
    std::transform(exercise.begin(),exercise.end(), s.begin(),to_str);
    std::for_each(s.begin(),s.end(), [](std::string val){std::cout << val;});
    std::cout << std::endl;
    
    //2
    std::string text="example";
    std::for_each(text.begin(),text.end(),[](char x){std::cout<< (char) toupper(x);});
    std::cout << std::endl;
    
    //3
    std::cout << std::count_if(exercise.begin(),exercise.end(),[](int x){return ((x%2) ? false : true); });
    std::cout << std::endl;
    //4
    std::cout<< "min =" << *(std::min_element(exercise.begin(),exercise.end())) << ",";
    std::cout<< "max =" << *(std::max_element(exercise.begin(),exercise.end()));
    std::cout << std::endl;
    //5
    auto it = remove_if(exercise.begin(),exercise.end(),[](int x){return ((x%2) ? true : false);});
    exercise.erase(it,exercise.end());
    std::for_each(exercise.begin(),exercise.end(), [](int val){std::cout << val << ",";});
    std::cout << std::endl;
    //7
    
    std::set<int> setContainer;
    std::for_each(exercise.begin(),exercise.end(), [&setContainer](int val){ setContainer.insert(val); });
    for (const auto& it : setContainer)
        std::cout << it << ",";
    std::cout << std::endl;
    //8
    
    
}

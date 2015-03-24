#include<iostream>
#include<vector>
#include<algorithm>
#include<string>


int main()
{
    std::string s1("vamshi");
    
    std::vector<int> vec;
    vec.push_back(5);
    vec.push_back(4);
    vec.push_back(3);
    vec.push_back(2);
    vec.push_back(1);
    std::sort(vec.begin(),vec.end());
    
    s1 = std::to_string(8.3);
    
    std::cout<<s1<<std::endl;
    
    s1 = std::stoi("abc 2",4,10);

    std::cout<<s1<<std::endl;

    std::vector<int> :: iterator itr;
    for(itr=vec.begin();itr !=vec.end();itr++)
        std::cout << *itr<<"  "<<std::endl;
}

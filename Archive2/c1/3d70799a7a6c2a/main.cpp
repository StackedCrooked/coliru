#include <fstream>
#include <string>
#include<iostream>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <boost/foreach.hpp>
#include <vector>


    //1. Get all words in "file.txt" and place it into a container
    //2. Count all words in the container
    //3. Is there a word "STL" in that file?
    //4. What is the last word?
    //5. What is the middle word?
    //6. How many words are there that has length greater than 3?
    //7. Remove all words whose length is less than 4
    //8. Print content of container
    
bool counter(std::string & str){
 
    if(str=="STL")
        return true;
    else
        return false;
    }
    
bool findlength(std::string & str2){
    if(str2.size()>3)
        return true;
    else
        return false;
    }
    
bool isless(std::string & str3){
     if(str3.size()<4)
        return true;
    else
        return false;
    }

int main()
{
    
    std::ifstream file("file.txt");
    std::istream_iterator<std::string> fileBegin (file);
    std::istream_iterator<std::string> fileEnd;
    
    std::vector<std::string> container;
    
    while(fileBegin != fileEnd)
    {
        container.push_back(*fileBegin);
        fileBegin++;
    }
        
//       for(auto const& val: container)
//    {
//        std::cout << val;
//    }
    
//    std::cout<<std::endl;
    //========================count words=================
    int size =0;
    size = container.size();
    std::cout<<size<<std::endl;
    
    //=============find STL============
    
    int counter2 = std::count_if(container.begin(), container.end(),counter);

    if (counter2>0) std::cout<<"there is an STL word"<<std::endl;
    else std::cout<<"there's no STL word"<<std::endl;
    
 
    
    //=========last word================
    
    std::string last = container.back();
    std::cout<<last<<std::endl;
    
    
    
    //=========middle word===========
    
    int mid = size/2;
    std::cout<<container[mid]<<std::endl;
    
    //=====length > 3=============
    
    int counter3 = std::count_if(container.begin(), container.end(),findlength);
    
    std::cout<<counter3<<std::endl;
    
    //===========remove if < 4 ===============
    
    std::vector<std::string>::iterator it2 = std::remove_if(container.begin(), container.end(), isless);
    container.erase(it2, container.end());
    
    
    //=========print content ================= :)
    
       for(auto const& val: container)
    {
        std::cout << val;
    }
    
    std::cout<<std::endl;
    
    


   
    
    
    
}

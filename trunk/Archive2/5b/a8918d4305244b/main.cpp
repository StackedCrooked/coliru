#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>

std::vector<std::string> container;

bool isLessThan(std::string text){
    if(text.size()>3)
    return true;
    else
    return false;
}

bool isLessThanAgain(std::string text){
    if(text.size()<4)
    return true;
    else
    return false;
}

int main(){
   
    std::ifstream ifs("file.txt");
    std::vector<std::string> container;
    std::string text;
    while(ifs >> text){
        container.push_back(text);   //1. Get all words in "file.txt" and place it into a container
    }
    
    int status = std::count(container.begin(), container.end(), "STL");
    
    if(status > 0)
        std::cout << "There is an STL word." << std::endl;
    else
        std::cout << "There is no STL word." << std::endl;
    
    
    std::cout << "Word count: " << container.size() << std::endl;   //2. Count all words in the container
    std::cout << "Last word: " << container.back() << std::endl;    //4. What is the last word?
    std::cout << "Middle word: " << container.at(container.size()/2) << std::endl;  //5. What is the middle word?
    int count = std::count_if(container.begin(), container.end(), isLessThan);
    std::cout << "Number of words that has length greater than 3: " << count << std::endl;     //6. How many words are there that has length greater than 3?
    std::vector<std::string>::iterator it = std::remove_if(container.begin(), container.end(), isLessThanAgain);
    container.erase(it, container.end());
    
    for(std::vector<std::string>::const_iterator it = container.begin(); it != container.end(); ++it)
    {
        std::cout << *it << " ";
    }
}
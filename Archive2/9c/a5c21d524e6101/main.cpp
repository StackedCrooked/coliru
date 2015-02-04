#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>
#include <algorithm>

bool isSTL(std::string input)
{
    if(input == "STL")
        return true;
    return false;
}

struct isGreaterThan3
{
    typedef std::string argument_type;
    bool operator () (const argument_type & x) const
    {
        return x.size() > 3;
    }
};

int main()
{
    std::vector<std::string> container;
    std::ifstream myfile("file.txt");
    std::istream_iterator<std::string> it(myfile);
    std::istream_iterator<std::string> eof;
    
    for(;it != eof; ++it)
        container.push_back(*it);
    int noOfWords = container.size();
    std::cout << "No. of words: " << noOfWords << std::endl;
    
    std::string STL = "STL";
    std::vector<std::string>::const_iterator stringIt = std::find_if(container.begin(), container.end(), isSTL);
    if(stringIt != container.end())
        std::cout << *stringIt << " is in the file." << std::endl;
        
    std::cout << "Last word is: " << *(container.rbegin()) << std::endl;
    std::cout << "Middle word is: " << *(container.begin() + noOfWords/2) << std::endl;
    
    int wordsGreaterThanThree = std::count_if(container.begin(), container.end(), isGreaterThan3());
    std::cout << "No. of words > 3: " << wordsGreaterThanThree << std::endl;
    
    std::vector<std::string>::iterator lessThan4 = std::remove_if(container.begin(), container.end(), std::not1(isGreaterThan3()));
    container.erase(lessThan4, container.end());
    
    for(std::vector<std::string>::iterator i = container.begin(); i != container.end(); ++i)
        std::cout << *i << " ";
        
    //1. Get all words in "file.txt" and place it into a container
    //2. Count all words in the container
    //3. Is there a word "STL" in that file?
    //4. What is the last word?
    //5. What is the middle word?
    //6. How many words are there that has length greater than 3?
    //7. Remove all words whose length is less than 4
    //8. Print content of container
}

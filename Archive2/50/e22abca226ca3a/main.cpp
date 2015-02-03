#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <iterator>
#include <functional>
#include <set>
#include <fstream>
#include <sstream>

void countWords(std::vector<std::string> container)
{
    std::cout << "Number of words: " << container.size() << std::endl;
}

void checkForSTL(std::vector<std::string> container)
{
    bool isSTL = false;
    if (*(std::find(container.begin(), container.end(), "STL")) == "STL")
        isSTL = true;
    std::cout << "Is STL exists: " << isSTL << std::endl;
}

void getLastWord(std::vector<std::string> container)
{
    std::cout << "LAST word: " << container.back() << std::endl;
}

void getMiddleWord(std::vector<std::string> container)
{
    std::cout<< "MiddleWord: " << container[container.size()/2] << std::endl;
}

bool isLengthLessThan4(std::string word){return (4 > word.length());}

void getWordsLessThan4(std::vector<std::string> container)
{
    std::cout << "Number of words less than 4: " << std::count_if(container.begin(), container.end(), isLengthLessThan4) << std::endl;
}

void removeWordsLessThan4(std::vector<std::string>& container)
{
    std::vector<std::string>::iterator iter = std::remove_if(container.begin(), container.end(), isLengthLessThan4);
    container.erase(iter, container.end());
}

int main()
{
    //1. Get all words in "file.txt" and place it into a container
    //2. Count all words in the container
    //3. Is there a word "STL" in that file?
    //4. What is the last word?
    //5. What is the middle word?
    //6. How many words are there that has length greater than 3?
    //7. Remove all words whose length is less than 4
    //8. Print content of container
    
    std::ifstream ifs("file.txt");
    std::string content((std::istreambuf_iterator<char>(ifs)),
                       (std::istreambuf_iterator<char>()));
                       
    std::istringstream iss(content);
    
    std::vector<std::string> container(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
    
    
    countWords(container);
    checkForSTL(container);
    getLastWord(container);
    getMiddleWord(container);
    getWordsLessThan4(container);
    removeWordsLessThan4(container);
    //std::cout << std::endl << content << std::endl << std::endl;
    
    std::cout << std::endl;
    for(std::vector<std::string>::const_iterator iter = container.begin(); iter != container.end(); ++iter)
    {
        std::cout << (*iter) << std::endl;
    }
    
    std::cout << std::endl<<std::endl;  
}

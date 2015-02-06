#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>
#include <set>

struct lengthover3 {
  bool operator() (const std::string& value) const {if (value.size()>3)return true; return false;}
  typedef std::string argument_type;
};

int main()
{
    //1. Get all words in "file.txt" and place it into a container
    std::cout<< "Get all words in \"file.txt\" and place it into a container" << std::endl;
    std::ifstream file("file.txt");
    std::vector<std::string> col((std::istream_iterator<std::string>(file)), std::istream_iterator<std::string>());
    std::copy(col.begin(), col.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout<<std::endl<< std::endl;
    
    //2. Count all words in the container
    std::cout<< "Count all words in the container" <<std::endl;
    std::cout<< "Number of words in container: " << col.size() <<std::endl<<std::endl;
    
    //3. Is there a word "STL" in that file?
    std::cout<< "Is there a word \"STL\" in that file?" <<std::endl;
    int count = std::count(col.begin(), col.end(), "STL");
    std::cout<< "Number of \"STL\" occurences: " << count <<std::endl<<std::endl;
    
    //4. What is the last word?
    std::cout<< "What is the last word?"<<std::endl;
    std::cout<< "Last word: " << col.at(col.size()-1)<<std::endl<<std::endl;
    
    //5. What is the middle word?
    std::cout<< "What is the middle word?"<<std::endl;
    std::cout<< "Middle word: " << col.at(col.size()/2) << std::endl <<std::endl;
    
    //6. How many words are there that has length greater than 3?
    std::cout<< "How many words are there that has length greater than 3?" << std::endl;
    count = std::count_if(col.begin(), col.end(), lengthover3());
    std::cout<< "Number of words that has length greather than 3: " << count<< std:: endl<<std::endl;
    
    //7. Remove all words whose length is less than 4
    std::cout<< "Remove all words whose length is less than 4" <<std::endl;
    std::vector<std::string>::iterator remove_it = std::remove_if(col.begin(), col.end(), std::not1(lengthover3()));
    col.erase(remove_it, col.end());
    std::cout<< "Resulting container :  ";
    std::copy(col.begin(), col.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout<<std::endl<< std::endl;
    
    //8. Print content of container
    std::cout<<"Print content of container"<<std::endl;
    std::cout<< "Resulting container :  ";
    std::copy(col.begin(), col.end(), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout<<std::endl<< std::endl;
    
    
    
    
    
}

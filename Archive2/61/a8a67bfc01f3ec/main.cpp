#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
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
    std::vector<std::string> file;
    std::string word;

    //1
    std::ifstream ifs ("file.txt", std::ifstream::in);
    do {
        char c = ifs.get();
        if(c == ' ' || c == '\n'){
            file.push_back(trim(word));
            word="";
        }else{
            word+=c;
        }
    }while (ifs.good());
	ifs.close();
    
    //2
    std::cout<< "2. count ="  << file.size();
   // auto stl= std::find_if(file.begin(), file.end(),  [](std::string x){return ((x.compare("STL")==0) ? true : false);});
   // std::cout<< "3. Is there a word STL in that file? "  << *stl;
    
    std::for_each(file.begin(),file.end(),[](std::string s){std::cout<<s<< " ";});
}

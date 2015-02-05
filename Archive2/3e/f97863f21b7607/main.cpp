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
            file.push_back(word);
            word="";
        }else{
            word+=c;
        }
    }while (ifs.good());
	ifs.close();
    std::cout<< "1. stored in file "  << std::endl;
    //2
    int count = file.size();
    std::cout<< "2. count ="  << count <<std::endl;
    auto stl= std::find_if(file.begin(), file.end(),  [](std::string x){return ((x.compare("STL")==0) ? true : false);});
    std::cout<< "3. Is there a word STL in that file? "  << ((*stl=="STL") ? "yes": "no") << std::endl;
    std::cout<< "4. What is the last word? "  << *(file.end()-1) << std::endl;
    std::cout<< "5. What is the last word? "  << (file[count/2]) << std::endl; 
    std::cout<< "6. How many words are there that has length greater than 3? "  << std::count_if(file.begin(),file.end(), [](std::string str){return ((str.length()>3) ? true : false);}) << std::endl;
    auto it =  std::remove_if(file.begin(),file.end(), [](std::string str){return ((str.length()<4) ? true : false);});
    file.erase(it, file.end());
    std::cout<< "7. Removed all words whose length is less than 4 " << std::endl;

    std::cout<< "8. Printing content of container " << std::endl;
    std::for_each(file.begin(),file.end(),[](std::string s){std::cout<<s<< " ";});
}

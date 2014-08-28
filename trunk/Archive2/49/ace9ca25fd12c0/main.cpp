#include <string>
#include <iostream>
#include <vector>
#include <map>
 
int main()
{
    std::vector<std::string> words = { 
        "this", "sentence", "is", "not", "a", "sentence",
	"this", "sentence", "is", "a", "hoax" 
    };
 
    std::map<std::string, size_t>  word_map;
    for (const auto &w : words) {
        ++word_map[w];
    }
 
    for (const auto &pair : word_map) {
        std::cout << pair.second
	          << " occurrences of word '"
	          << pair.first << "'\n";
    }
}
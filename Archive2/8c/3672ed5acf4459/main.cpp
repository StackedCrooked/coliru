#include <iostream>
#include <unordered_map>
#include<stdio.h>
 
int main()
{
    std::unordered_map<char, int> letter_counts {{'a', 27}, {'b', 3}, {'c', 1}};
 
    std::cout << "initially:\n";
    for (const auto &pair : letter_counts) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
 
    letter_counts['b'] = 42;  // update an existing value
 
    letter_counts['x'] = 9;  // insert a new value
 
    std::cout << "after modifications:\n";
    for (const auto &pair : letter_counts) {
        std::cout << pair.first << ": " << pair.second << '\n';
    }
    
    FILE *in;
	char buff[512];

	if(!(in = popen("sudo id", "r"))){
		return 1;
	}

	while(fgets(buff, sizeof(buff), in)!=NULL){
		std::cout << buff;
	}
	pclose(in);

	return 0;
}

    
    

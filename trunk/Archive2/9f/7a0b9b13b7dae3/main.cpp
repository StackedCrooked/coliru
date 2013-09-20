#include <iostream>
#include <string>
#include <ctype.h>

int main()
{
    int width, height;
    std::string str;
    char** charTable;
    
    
    std::cin >> width;
    std::cin >> height;
    std::cin >> str;
    
    charTable = new char*[height];
    for(int i = 0; i < height; i++){
        charTable[i] = new char[width*27];
    }
    
    std::cin.ignore();
    
    //For each line of the ASCII art alphabet
    for(unsigned int i = 0; i < height; i++){
        std::string temp;
        getline(std::cin, temp);
        
        for(unsigned int j = 0; j < temp.size(); j++){
            charTable[i][j] = temp[j];
        }
    }
    
    char** result = new char*[height];
    for(int i = 0; i < height; i++){
        result[i] = new char[width*str.size()];
    }
    
    for(unsigned int i = 0; i < str.size(); i++){
        
        short code = toupper(str[i]);
        code -= 65;
        
        if(code >= 0 && code < 26){
            for(unsigned int j = 0; j < height; j++){
                for(unsigned int k = 0; k < width; k++){
                    result[j][width*i + k] = charTable[j][width*code + k];
                }
            }
        }else{
            for(unsigned int j = 0; j < height; j++){
                for(unsigned int k = 0; k < width; k++){
                    result[j][width*i + k] = charTable[j][width*26 + k];
                }
            }
        }
    }
    
    for(unsigned int i = 0; i < height; i++){
        for(unsigned int j = 0; j < width*str.size(); j++){
            std::cout << result[i][j];
        }
        std::cout << std::endl;
    }
    
    for(int i = 0; i < height; i++){
        delete [] result[i];
        delete [] charTable[i];
    }
    delete [] result;
    delete [] charTable;
    
    return 0;
}
#include <iostream>
#include <string>

bool add(std::string& animal, int number)
{std::cout << "add\n"; return true;}
bool del(std::string& animal)
{std::cout << "del\n"; return true;}

int main() {
    char command;
    std::string animal;
    int number;
    bool valid = true;
    while(std::cin >> command && valid) { 
        switch(command) {
            
        case 'A': 
            if (std::cin >> animal >> number)
                valid = add(animal, number);
            else
                valid = false;
            break;
            
        case 'D':
            if (std::cin >> animal)
                valid = del(animal);
            else
                valid = false;
            break;
            
        default:
            std::cout << "invalid command\n";
            valid = false;
        }
    }
    return 0;
}

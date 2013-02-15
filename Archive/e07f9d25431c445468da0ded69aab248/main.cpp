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
            break;
            
        case 'D':
            if (std::cin >> animal)
                valid = del(animal);
            break;
            
        default:
            std::cout << "invalid command\n";
            valid = false;
        }
        if (!std::cin)
            std::cout << "invalid parameters\n";
    }
    return 0;
}

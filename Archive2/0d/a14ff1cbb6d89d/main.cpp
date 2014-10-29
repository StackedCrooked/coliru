#include <iomanip>
#include <iostream>
#include <vector>

int main()
{
    /* std::vector<std::string> headers = {
        "First name",
        "Last name",
        "Age"
    };
    
    std::vector<std::string> fields = {
        "Jane", "Doe", "20",
        "John", "Doe", "18"
    }; */
    
    std::vector<int> headers = { 1, 2, 3 };
    std::vector<int> fields = { 4, 5, 6 };
    
    int max_length = std::max(std::max(headers.begin(), headers.end()), std::max(fields.begin(), fields.end()));
    std::cout << max_length;
}
#include <vector>
#include <string>
#include <iostream>
 
struct President
{
    std::string name;
    std::string country;
    int year;
 
    President(std::string p_name, std::string p_country, int p_year)
        : name(p_name), country(p_country), year(p_year)
    {
        std::cout << "I am being constructed.\n";
    }
    President(President& other) = delete;
};
 
int main()
{
    std::vector<President> elections;
    std::cout << "emplace_back:\n";
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);
}
#include <forward_list>
#include <string>
 
int main()
{
    // c++11 initializer list syntax:
    std::forward_list<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};
 
    // words2 == words1
    std::forward_list<std::string> words2(words1.begin(), words1.end());
 
    // words3 == words1
    std::forward_list<std::string> words3(words1);
 
    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    std::forward_list<std::string> words4(5, "Mo");
 
    return 0;
}
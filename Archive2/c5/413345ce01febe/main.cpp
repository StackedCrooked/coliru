#include <deque>
#include <string>
 
int main() 
{
    // c++11 initializer list syntax:
    std::deque<std::string> words1 {"the", "frogurt", "is", "also", "cursed"};
 
    // words2 == words1
    std::deque<std::string> words2(words1.begin(), words1.end());
 
    // words3 == words1
    std::deque<std::string> words3(words1);
 
    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    std::deque<std::string> words4(5, "Mo");
}
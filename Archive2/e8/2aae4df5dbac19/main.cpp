#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>
 
int main()
{
    std::srand(std::time(0));
    
    // Store the answers
    std::vector<std::string> answers = { "Answer1" , "Answer2", "Answer3", "Answer4" };
    
    for(std::size_t n = 0 ; n <10 ; ++n)
    {
        // Randomize the vector
        std::random_shuffle(std::begin(answers), std::end(answers));
        std::cout << answers[0] << '\n';
    }
}
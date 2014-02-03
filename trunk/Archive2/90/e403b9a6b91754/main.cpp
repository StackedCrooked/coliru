#include <algorithm>
#include <iterator>
#include <iostream> // you forgot this
#include <string>   // you forgot this

int main()
{
    using namespace std;    // you forgot this
    
    // let's pretend this is the string
    string myAnimal = "Please enter the name of your favorite animal.";
    
    // keep the loop variable local, prefer pre-increment
    for (int i = 0; i < myAnimal.length(); ++i)
        cout << myAnimal[i] << "|";    // prefer [] over at()
    std::cout << "\n";

    // C++11 range-for
    for (auto c : myAnimal)
        std::cout << c << "|";
    std::cout << "\n";
    
    // index-based reverse loop
    for (int i = myAnimal.length() - 1; i >= 0; --i)
        cout << myAnimal[i] << "|";
    std::cout << "\n";
    
    // algorithm-based reverse loop
    std::copy(myAnimal.rbegin(), myAnimal.rend(), ostream_iterator<char>(cout, "|"));
    std::cout << "\n";
    
    // main implicitly return 0
}

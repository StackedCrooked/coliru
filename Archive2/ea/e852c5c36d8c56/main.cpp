#include <iostream>

int main()
{
    using namespace std;

    const float dollar = 1.00;
    
    std::cout.precision(2);
    std::cout.setf(std::ios::fixed);
    cout << "You have " << dollar*10.00 << " dollars." << endl;

    cin.get();
    cin.get();

    return 0;
}
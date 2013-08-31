#include <iostream>
#include <limits>
using namespace std;

int main()
{
    int age;
    bool error = false;
    do
    {
        cout << "Please enter your age\n";
        error = true;

        if (!(cin >> age))
        {
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!cin.good())
                break;
        } else if (age > 105)
        {
            cout << "You're Too Old\n";
        }
        else if (age < 1)
        {
            cout << "You haven't been born yet!\n";
        }
        else
        {
            error = false;
        }
    } while (error);

    if (!error)
    {
        cout << "Your age is: " << age << "\n";
    } else
    {
        cout << "Age not successfully read\n";
    }
}

#include <iostream>
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
            cin.ignore(1<<22ul, '\n');
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

    cout << "Your age is: " << age << "\n";
    return 0;
}

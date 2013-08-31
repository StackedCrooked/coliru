#include <iostream>

int main()
{ using namespace std;

int grade = -1; // grade will hold grade value; initialized to -1
do {
    cout << "Please enter a grade value between 0 and 100." << "\n";
    if (!(cin >> grade))
    {
      cin.clear();
    }
} while (grade < 0 || grade > 100);

cout << grade << "\n";

return 0;

}
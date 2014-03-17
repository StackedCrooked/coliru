#include <iostream>
using namespace std;
char letter;
float x;
float y;
float z;
int main()
{
    cout << "What is the shape: Enter t for right triangle";
    cin >> letter;
    if (letter == 't')
    {
      cout << "Enter the hight";
      cin >> x;
      cout << "Enter length of the base";
      cin >> y;
      cout << "\n" << "The Area is :" << 0.5 * x * y << endl;
    }
    return 0;
}
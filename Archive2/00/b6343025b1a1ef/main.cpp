#include <iostream>
#include <string>
using namespace std;
 
int main() {
 
    std::string array[] = {"Oneeeeeeeeeeeeeeeeee", "Twooooooooooooooooo", "Threeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee"};
    int num_strings = sizeof(array)/sizeof(array[0]);
 
    cout << "sizeof(array): " << sizeof(array) << endl;
    cout << "sizeof(array[0]): " << sizeof(array[0]) << endl;
    cout << "sizeof(array[1]): " << sizeof(array[1]) << endl;
    cout << "sizeof(array[2]): " << sizeof(array[2]) << endl;
 
    cout << num_strings << endl;
	return 0;
}
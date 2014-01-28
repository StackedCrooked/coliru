

// This program asks for personal information and displays it afterward. 
#include <iostream> 
#include <string> 
using namespace std;
int main () { 
string firstName, lastName, Street, City, State, Zip, Phone, Major;

cout << "What is your first name? "; 
cin >> firstName; 
cout << "What is your last name? "; 
cin >> lastName; 
cout << "What is your street address? "; 
cin >> Street; 
cout << "What city do you reside in "; 
cin >> City; 
cout << "What state is that in? "; 
cin >> State; 
cout << "Next, What is your zipcode? "; 
cin >> Zip; 
cout << "What is your telephone number? "; 
cin >> Phone; 
cout << "Finally, what is your current major? "; 
cin >> Major; 
// Display all information. 
cout << "Thank you, " << firstName << "." << endl; 
cout << "Your information is: \n"; 
cout << firstName << " " << lastName << endl; 
cout << Street << endl; 
cout << City << ", "<< State << " " << Zip << endl; 
cout << Phone << endl; 
cout << endl; 
cout << "Oh, and you're major is " << Major << "."; 
system ("PAUSE"); 
return 0;
}

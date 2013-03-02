#include <iostream>
using std::cout;
using std::cin;
using std::endl;

void print() {
    cout << "These are the options:" << endl;
    cout << "  1: Add to front" << endl;
    cout << "  2: Add to back"  << endl;
    cout << "  3: Remove"       << endl;
    cout << "  4: Print list"   << endl;
    cout << "  5: Print list count" << endl;
    cout << "  6: Exit"         << endl;
    cout << endl;
}

void printList() {
    cout << "What list?" << endl;
    cout << endl;
}

void printItem() {
    cout << "What list size?" << endl;
    cout << endl;
}

void addValueFront() {
    cout << "Add to front of what?" << endl << endl;
}

void addValueBack() {
    cout << "Add to back of what?" << endl << endl;
}

void removeValue(int n) {
    cout << "Remove " << n << " from what?" << endl << endl;
}

int main()
{
   int userChoice = 0;

  print(); //printing all of the options.

  cout << "Please enter one of the options listed below" <<endl;
  cin >> userChoice;

  while(userChoice != 6)// 6 = the user wishing the end the program when they press 6.
  {
     if(userChoice == 1) //adding integer to the front of the list
         {
            addValueFront();
         }
         else if(userChoice == 2)//adding integer to the back of the list
         {
            addValueBack();
         }
         else if(userChoice == 3)//removing from the list
         {
             int n = 0;
             cout << "Please enter the integer you wish to remove" << endl;
             cin >> n;
             removeValue(n);
         }
         else if(userChoice == 4)//printing the list
         {
             printList();
         }
         else if(userChoice == 5)//printing the number of items from the list
         {
             printItem();
         }

         else
         {
             cout << "The number you have entered is too high. Please try again" << endl;
         }

         cout << "please enter another option" <<endl;

     cin >> userChoice; //sets up which option the user can choose from.
   }
   
   return 0;
}
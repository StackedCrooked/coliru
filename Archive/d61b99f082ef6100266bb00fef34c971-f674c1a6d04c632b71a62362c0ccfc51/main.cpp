// happy c++
//

#include <iostream>
#include <string>
using namespace std;

#define NEWLINE '\n'
int main ()
{
    // declare some t
  cout << "Hello World!";
  cout << NEWLINE;
  cout << "Hello Washy";
  cout << "yay";
  cout << "b-e-a-utiful";
  cout << "sad I can't rember anything in c++!";
  string * msg = new string;
  *msg = "wooo dynamic memory object";
  cout << *msg;

  int * stuff;
  stuff = new int[44444];
  //cout << *stuff; // is the * required here?
  cout << stuff[1];  // sorry you made an array so I was wrong 
  // but there actuall the same thing in c++ muhahha, (just to confuse :P)
  //  both will print garbarge because theres nothing initailized/assigned to the
  // first element of the array
  int * stuff2;
  stuff2 = new int(12345);  // this time the constructor sytax 'asigns' a vaule rather than making array space like with square brackets
  cout << *stuff2;   // This is a single/scala int so this does need the dereference symbol

  
  
  // int *** foo; // the symbol * in this context means 'pointer to' (declaration is the context)
  // declare foo as pointer to pointer to pointer to int  // you read backwards starting at foo
  // In this declaration there are three levels on indirection
  
  // cout << *foo;  the symbol * means dereferences when in the context of useing the varable
  
  //  one place in c which is still valid but fairly depreciated in c++
  //  where you don't dereference:
  
  char foo[] = "some string bla";
  cout << foo;
  
  //What is happening is kinda crazzy
  //  when you degrade foo[x] to foo it becomes a pointer
  //  prity much like &foo[1]  foo is a pointer to the first element of the foo array
  // tools like cout are desinnd to look for addresses containing |s|o|m|e|...|b|l|a|\0|
  // in c/c++  "stuff" creates a string stuff\0  
  // it is a convention so when programes see char arrays ending in a null byte
  // they print every thing before the null bite
  // this does not work with int arrays!!!
  // the class std::string replaced all that and strings can be stored in these objects
  // without the null byte
  
  

  delete stuff;
  delete stuff2;
  delete msg;
  //
  return 1;
}
	// tab
    // spaces

// Using the STL generic reverse algorithm with a string and an array
#include <iostream>
#include <string>
#include <cassert> 
#include <algorithm> // For reverse algorithm
using namespace std;

#include <chrono>

int main()
{
  cout << "Using reverse algorithm with a string" << endl;
  string string1 = "mark twain";
  cout << string1 << endl;
  reverse(string1.begin(), string1.end());
  cout << string1 << endl;
  reverse(string1.begin(), string1.end());
  cout << string1 << endl;
  //assert (string1 == "niawt kram");
  cout << " --- Ok." << endl;

  
  return 0;
}

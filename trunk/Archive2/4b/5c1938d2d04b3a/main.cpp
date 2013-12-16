#include <iostream>
using namespace std;

int main()
{
  int WheatPrice, BarleyPrice, CanolaPrice;
  
  cout << "Wheat Price: ";
  cin >> WheatPrice;
  
  cout << endl << "Barley Price: ";
  cin >> BarleyPrice;
  
  cout << endl  << "Canola Price";
  cin >> CanolaPrice;
  
  cout << endl << endl <<"Value of 1 Hectare of Wheat: " << (WheatPrice*24);
  cout << endl << "Value of 1 Hectare of Barley: " << (BarleyPrice*22);
  cout << endl << "Value of 1 Hectare of Canola: " << (CanolaPrice*12);
  
  char f;
  cin >> f;
  return 0;
}
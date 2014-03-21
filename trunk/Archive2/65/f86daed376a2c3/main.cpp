#include <fstream>
#include <iostream>
#include <string>

int main() {
  using namespace std;
  cout << "Enter a file name. " << endl;

  string name;
  cin >> name;
  fstream input(name);

  if (input) {
    double total = 0;
    double count = 0;
    double n;
    while (input >> n) {
      total = total + n;
      count++;
    }
    double average = total / count;
    cout << "sum " << total << " count " << count << " average " << average
         << endl;
  } else {
    cout << "Error opening file\n";
  }
}

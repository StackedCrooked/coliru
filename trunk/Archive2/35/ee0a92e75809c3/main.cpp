#include <ctime>
#include <iostream>
#include <sstream>

using namespace std;

string getTime(int dayOfYear) {
  int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  int month = 0;
  int dayOfMonth = 0;
  for (int i = 0; i < dayOfYear - 1; i++) {
    dayOfMonth++;
    if (dayOfMonth >= months[month]) {
      month++;
      dayOfMonth = 0;
    }
  }
  ostringstream oss;
  oss << (month+1) << "/" << (dayOfMonth+1) << "/2013";
  return oss.str();
}

int main() {
  cout << getTime(180) << endl;
}
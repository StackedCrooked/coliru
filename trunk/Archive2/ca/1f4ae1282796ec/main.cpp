#include <ctime>
#include <iostream>

using namespace std;

void printTime(int dayOfYear) {
  std::tm t = {};
  t.tm_year = 2013-1900;
  t.tm_mday = dayOfYear;
  mktime(&t);
  char buffer[11];
  strftime(buffer, 11, "%m/%d/%Y", &t);
  cout << buffer;
}

void printTime(int dayOfYear, char* buffer) {
  std::tm t = {};
  t.tm_year = 2013-1900;
  t.tm_mday = dayOfYear;
  mktime(&t);
  strftime(buffer, 11, "%m/%d/%Y", &t);
}

int main() {
  printTime(180);
  cout << endl;

  char buffer[11];
  printTime(180, buffer);
  cout << buffer << endl;
}
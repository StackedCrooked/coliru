#include <ctime>
#include <iostream>

using namespace std;

void printTime(int dayOfYear) {
  std::tm t = {};
  t.tm_year = 2013-1900;
  t.tm_mday = dayOfYear;
  std::mktime(&t);
  char buffer[11];
  std::strftime(buffer, 11, "%m/%d/%Y", &t);
  std::cout << buffer;
}

int main() {
  printTime(180);
}
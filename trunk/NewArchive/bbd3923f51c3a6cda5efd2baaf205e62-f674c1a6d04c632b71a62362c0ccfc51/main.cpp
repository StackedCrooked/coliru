#include <iostream>
#include <iomanip>
#include <locale>
#include <sstream>
#include <string>
using namespace std;

class test {
public:
  test(string hw, int tree, string vate);
  ~test() {

  }
  string helloworld;
  int three;
  string privacy() {
    cout << "I will now access the  private variable PRI\n";
    cout << "pri = private\n";
    cout << "The value of PRI is "+pri+"\n";
  }
private:
  string pri;
};

test::test (string hw, int tree, string vate) {
helloworld = hw;
three = tree;
pri = vate;
}

int main() {
  cout << "We will now perform an object test!\n";
  test thing ("hello world", 3, "private");
  cout << "thing.helloworld\n";
  cout << "hello world\n";
  cout << "Real value: "+thing.helloworld+"\n";
  cout << "thing.three\n";
  cout << "3\n";
  ostringstream thee;
  thee << thing.three;
  string result = thee.str();
  cout << "Real value: "+result+"\n";
  cout << "thing.privacy()\n";
  cout << "Real value:\n";
  thing.privacy();
  return 0;
}
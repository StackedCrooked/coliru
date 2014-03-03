#include <iostream>

using namespace std;

class INT {
public:
            INT(int ii = 0) : i(ii) {}
            operator int&() { return i; }
            void display()
            {
              cout << "value of i is : " << i;       
            }
private:
  int i;
};

int main()
{
  INT l;
  l.display();
  return 0;
}
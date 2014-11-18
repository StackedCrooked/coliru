#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

char * ident(char *p) {return p;}
int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;

//r value reference
int &&rri = {1};        cout<<++rri << endl;
int &&rri1 = 1;         cout<<++rri1<< endl;

const int &ri = {1};    cout<<ri<< endl;
const int &rci = 1;     cout<<rci<< endl;

const double &cdr = 1;  cout<<cdr<< endl;
const double &cdr1 = {1};   cout<<cdr1<< endl;

  int arr[10]={1,3,8,7,6,2,4,9,7,0};
  
  int count[10] = {0};
  for(int i=0; i<10; i++)
  {
      count[arr[i]] ++;
  }
  for(int i=0; i<10; i++) cout<<count[i];
  
 
}

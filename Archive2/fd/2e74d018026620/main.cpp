#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Bar
{
public:
  Bar(vector<unique_ptr<char>> vec);
  vector<unique_ptr<char>> vec_;
};

Bar::Bar(vector<unique_ptr<char>> vec) :
  vec_(move(vec)) //not ok
{
}

int main()
{
  vector<unique_ptr<char>> vec;
  vec.push_back(unique_ptr<char>(new char('a')));
  vec.push_back(unique_ptr<char>(new char('b')));
  vec.push_back(unique_ptr<char>(new char('c')));
  vector<unique_ptr<char>> vec1 (move(vec)); //ok
  Bar bar(std::move(vec1));
  return 0;
}
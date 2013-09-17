#include <queue>
#include <stack>
#include <iostream>

using namespace std;

template<class T>
auto topfront(T const& p)->decltype(p.top())
{  return p.top();  }

template<class T>
auto topfront(T const& p)->decltype(p.front())
{  return p.front();  }

template <typename T>
void example()
{
  T a;
  a.push(3);
  a.push(1);
  a.push(2);
  while (!a.empty()) {
    cout << topfront(a) << ' ';
    a.pop();
  }
  cout << endl;
}

int main()
{
    example<queue<int>>();
    example<stack<int>>();
}

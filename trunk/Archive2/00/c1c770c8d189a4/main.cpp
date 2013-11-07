#include <vector>
#include <cassert>
using namespace std;

/* I cheat and make my stack just wrap a vector */
template<typename T>
class stack
{
  private:
    vector<T> v;

  public:
    bool empty() const { return v.size() == 0; };

    T pop() { 
        T& t = v.back();
        v.pop_back();
        return t;
    }

    void push(T const& u) { v.push_back(u); }
};

template<typename T>
class queue
{
  private:
    stack<T> s;

  public:
    bool empty() const { return s.empty(); };

    T pop() {
        stack<T> temp;
        T t = s.pop();

        while(!s.empty()) {
            temp.push(t);
            t = s.pop();
        }

        while(!temp.empty())
            s.push(temp.pop());

        return t;
    };

    void push(T const& t) { s.push(t); }
};

int main() {
    stack<int> s;
    for(int i = 0; i < 10; ++i) {
      s.push(i);
    }
    assert(s.pop() == 9);
  
    queue<int> q;
    for(int i = 0; i < 10; ++i) {
        q.push(i);
    }
    assert(q.pop() == 0);
  
    return 0;
}
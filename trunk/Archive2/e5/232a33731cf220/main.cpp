#include <map>
struct A
{
  int bla;
  A(int blub):bla(blub){}
  A(A&&) = delete;
  A(const A&) = delete;
  A& operator=(A&&) = delete;
  A& operator=(const A&) = delete;
};
int main()
{
  std::pair<int, A> x(1, 4);
}
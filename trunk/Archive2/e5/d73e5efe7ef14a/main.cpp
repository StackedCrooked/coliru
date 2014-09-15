#include <vector>
#include <list>
#include <set>
class getRandomN 
{
  int count;
 
public:
  getRandomN(int n = 1) : count(n) {}
 
  template <class Container>
  operator Container () {
    Container c;
    for(int i = 0;i < count; ++i)
      c.insert(c.end(), 1); // push_back is not supported by all standard containers.
    return c;
  }
};
 
int main()
{
  std::set<int> random_s = getRandomN(10);
  std::vector<int> random_v = getRandomN(10);
  std::list<int> random_l = getRandomN(10);
}
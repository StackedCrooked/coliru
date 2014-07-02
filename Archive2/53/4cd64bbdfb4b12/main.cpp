#include <utility>

template <template <typename, typename> class Pair, typename Value>
struct list
{
  Pair<Value, list *> node;
};

int main()
{
  typedef list<std::pair, int> int_list;
  int_list l, *head = &l;
  for (int i = 1; i < 10; ++i)
  {
    head->node.first = i;
    head->node.second = new int_list;
    head = head->node.second;
  }
}

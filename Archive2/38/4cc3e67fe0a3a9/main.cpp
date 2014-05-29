#include <functional>

struct Node {
    size_t length;
};

template<typename N>
class C {
public:
  C()
  : f([this](N node) {
        if(node->length > longest) longest = node->length;
      })
  {}
  size_t longest = 0;
  std::function<void(const N )> f;
};

int main() {

  Node n;
  n.length = 5;
  C<Node*> c;
  c.f(&n);
}

#include <iostream>
#include <string>
#include <vector>
#include <utility>

template <typename S>
class SuffixTree {
    typedef S string;
    S haystack;
    class Node {
    public:
        typedef std::pair<int, int> substring;
        std::vector<std::pair<substring, Node*>> g;
        S test;
        Node *parent;
    };
    
    class Base {
    public:
        Node *root;
        S test;
        Base() {
            root = new Node();
            std::cout << "New node created" << std::endl;
        }
        ~Base() {
            delete root;
            std::cout << "Wohooo" << std::endl;
        }
    };
    Base tree;
public:
    SuffixTree() : tree() {}
    ~SuffixTree() {}
    void test(S xxx) {
        tree.test = xxx;
        std::cout << tree.test << std::endl;
    }
};

int main(int, char**){
  SuffixTree<std::string> blob;
  std::cout << "blob" << std::endl;
  blob.test("cacao");
  return 0;
}

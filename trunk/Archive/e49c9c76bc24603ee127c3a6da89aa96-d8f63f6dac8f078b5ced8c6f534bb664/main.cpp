#include <iostream>
#include <vector>
#include <string>

struct Node {
    std::string data;
	std::vector<StringTree*> children;
}

std::string to_json(const Node& tree) {
	return ""
}

/*
         r
        / \
       /   \
      /     \
     a       d
    / \       \ 
   /   \       \
  /     \       \
 b       c       e
                / \
               /   \
              /     \
             f       g
*/
int main() {
	Node g;
	g.data = "g";
	
	Node f;
	f.data = "f";
	
	Node e;
	e.data = "e"
	e.children.push_back(&f);
	e.children.push_back(&g);
	
	Node b;
	b.data = "b"
	
	Node d;
	d.data = "d"
	d.children.push_back(&e);
	
	Node a;
	a.data = "a"
	a.children.push_back(&b);
	a.children.push_back(&c);
	
	Node r;
	r.data = "r"
	r.children.push_back(&a);
	r.children.push_back(&d);
	
	std::cout << to_json(r) << "\n=======================";
}
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct employee {std::string name; double salary;};
struct document {document(std::string, int) {}};


int main() {
std::vector<int> v {9,3}; // std::initializer_list<int> (2)
        employee e {"John Doe", 10000}; // aggregate (1)
        document d {"New Doc", 5}; // document ctor (3)

             int i1 {5}; // legal, but yucky
             int i2 = 5; // still better
//     vector<int> v ();  // uhoh, „C++ most vexing parse“
     vector<int> v1 {};  // ok
     
     (void)i1;
     (void)i2;
}
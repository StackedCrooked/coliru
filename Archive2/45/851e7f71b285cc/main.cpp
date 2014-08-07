#include <iostream>
#include <string>
#include <exception>

using namespace std;

namespace YAML{
    struct Node{
        string name;
    };
    
    Node LoadFile(string filepath){
        return {filepath};
    }
    
    
}

YAML::Node ParseFromFile(const string& filepath) {
        YAML::Node yaml;
        try {
            return YAML::LoadFile(filepath);
        } catch(const exception& e) {
            cout << "error";
        }
        return { "" }; // should return some value otherwise you'll get a warning
}

class A {
 public:
  A(YAML::Node yaml) {
    cout  << "Got" << endl;
  }
  A(const string& filepath) : A(ParseFromFile(filepath)) {}
};


int main(int argc, char** argv) {
  A a(string(argv[1]));  // this is not a variable but a funtion declaration;  
  A a1 = A(string(argv[1]));
  A a2 = A(argv[1]);
  YAML::Node yaml = ParseFromFile(string(argv[1]));
  A b(yaml);
  return 0;
}
#include <string>

struct MyClass {
  std::string version;
  void setVersion(std::string&& ver) { version = std::move(ver); }
};

std::string getVersion() { return "version2"; }

int main() {
  MyClass a;
  std::string v1 = "version1";
  a.setVersion(v1);           // lvalue
  a.setVersion(getVersion()); // rvalue
  a.setVersion("version3");   // rvalue as well
}
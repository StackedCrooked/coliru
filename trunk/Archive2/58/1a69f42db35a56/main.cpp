// kapitel016/thread02.cpp
#include <thread>
#include <iostream>

void func(std::string str) {
  std::cout << "Thread als Funktion\n";
  std::cout << "Daten(Funktion): " << str << std::endl;
}

class funcObj {
public:
  void operator()(double val) const {
    std::cout << "Thread als Funktionsobjekt\n";
    std::cout << "Daten(Funktor): " << val << std::endl;
  }
};


int main() {
  std::string text("Ein Text");
  std::thread t1(func, text);
  funcObj fobj;
  std::thread t2(fobj, 3.1415);
  int ival = 1234;
  std::thread t3([ival, text] {
    std::cout << "Thread als Lambda-Funktion\n";
    std::cout << "Daten(Lambda): " << ival << std::endl;
    std::cout << "Daten(Lambda): " << text << std::endl;
  });
  t1.join();
  t2.join();
  t3.join();
}
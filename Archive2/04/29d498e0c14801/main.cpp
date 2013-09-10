#include <iostream>

class Packet{
private:
  char *contents;

public:
  void pack() {
      std::cout << "Pack!" << std::endl;
  }
};

class Worker{
public:
  void fill_packet(Packet *a){
    a->pack();
  };
};


int main() {
    
    Worker Me;
    Packet MyStash;
    Me.fill_packet(&MyStash);
    return 0;
}
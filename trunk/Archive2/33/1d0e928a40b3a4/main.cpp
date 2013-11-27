#include <iostream>

class ZombieFetus{
  private:
  public:
  ZombieFetus();
};

ZombieFetus::ZombieFetus(){
  std::cout << "http://www.metal-archives.com/band/view/id/55878" << std::endl;
};

class FaceOfAVirus{
  private:
  public:
  FaceOfAVirus(int);
};

FaceOfAVirus::FaceOfAVirus(int i){
  std::cout << "http://www.metal-archives.com/band/view/id/74239" << std::endl;
};


int main(int argc, char **argv){
  std::cout << "some random bands :" << std::endl;
  ZombieFetus  band1();
  FaceOfAVirus band2(0);
}
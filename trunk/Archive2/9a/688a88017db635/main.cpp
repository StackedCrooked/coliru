#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <future>
#include <cstdint>
#include <memory>
#include <string>
#include <chrono>

using namespace std;

struct image {
    image(char c) : str(50, c) {}
    void render() const { cout << str << endl;}
    char value() const { return str[0];}
    
    string str;
};

template <typename Img>
auto call_filter(Img& img) {
    // invoke worker thread
    return std::async([&img, in=img](){
      // filter
      this_thread::sleep_for(chrono::milliseconds(500));
      shared_ptr<image const> out = make_shared<image>(in->value() + 1);
      img = out;
  });
}

int main() {
  shared_ptr<image const> img = make_shared<image>('a');
  
  for (int num = 5; num; --num) {
      // GUI thread render & initiate filter call
      auto f = call_filter(img);
      for (int n = 5; n; --n) {
          // render image
          this_thread::sleep_for(chrono::milliseconds(277));
          auto local = img;
          local->render();
      }
      f.wait();
  }
}
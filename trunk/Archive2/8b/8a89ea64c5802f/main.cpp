#include <boost/format.hpp>
#include <iostream>
#include <vector>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>
using std::vector;
using std::cout;

class button
{
 public:
  boost::function<int (int)>onClick;
 };

class player
 {
 public:
  void play(int i) {printf("i: %d",i); };
  void stop(){};
 };


 int main()
 {
   button playButton, stopbutton;
   player thePlayer;

   playButton.onClick=boost::bind(&player::stop,thePlayer);
   int i=2222;
   boost::bind(&player::play,thePlayer,_1)(i);
   playButton.onClick(100);
   stopbutton.onClick=std::bind1st(std::mem_fun(&player::play),&thePlayer);
   stopbutton.onClick(500);
 }


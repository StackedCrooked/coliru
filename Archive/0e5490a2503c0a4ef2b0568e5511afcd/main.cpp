#include <thread>
#include <iostream>
#include <random>
#include <future>
#include <vector>
#include <random>

#define N 10000

typedef std::mt19937 MyRNG;  
uint32_t seed_val;           
MyRNG rng;         

void init(){
  rng.seed(time(NULL));
}

std::normal_distribution<double> normal_dist(0.0, 1.0);

double rnorm(){
  double sum;
  for(int i = 0; i < N; i++){
    sum += normal_dist(rng);
  } 
  return sum;
}

int main(){
  std::vector<std::future<double> > futures;

  for(int i = 0; i < 4; ++i){
    std::packaged_task<double()> pt(rnorm);
    futures.push_back(pt.get_future());

    //error here with some things i've tried
    //std::thread(std::move(pt)).detach();
    //std::thread task(std::move(pt));
    std::thread(std::move(pt)).detach();
  }

  return 0;
}
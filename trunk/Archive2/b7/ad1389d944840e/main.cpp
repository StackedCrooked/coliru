#include <iostream>
#include <iomanip>
#include <random>

//This is a simulator for enhancing tyrant equipment pieces in Global MapleStory v157 using the Star Force Enhancement System

int main()
{
  const int equipNum=100000; //number of equips simulated
  int numTries[equipNum], numDestroy[equipNum];
  int successRate[]={50,50,45,40,40,40,40,40,40,37,35,35,3,2,1}, destroyRate[]={0,0,0,0,0,3,5,7,10,15,20,25,50,50,50};
  int consecutiveFails=0,currentStars=-1,previousStars=0,desiredStars=0,a=-1;
  double averageNumTries=0,averageNumDestroy=0,averagecost=0;

 std::default_random_engine engine;
 std::uniform_real_distribution<double> gen(0.0, 1.0);
  
  while(desiredStars>15 || desiredStars<1){
    std::cout << "Please enter the desired number of stars (up to 15): ";
    std::cin >> desiredStars;
  }
  while(a<0||a>desiredStars){
    std::cout << "Please enter the current number of stars (up to 14): ";
    std::cin >> a;
  }

  currentStars=a;
  
  for(int i=0;i<equipNum;i++){numTries[i]=0;numDestroy[i]=0;}
  for(int i=0;i<equipNum;i++){

    while(currentStars<desiredStars){
      if(consecutiveFails==2&&previousStars!=0){ //Chance Time!
        consecutiveFails=0;
        currentStars++;
      }
      
      else if(gen(engine)*100<successRate[currentStars]){ //Pass
        previousStars=currentStars;
        consecutiveFails=0;
        currentStars++;
      }
      else if(gen(engine)*100<destroyRate[currentStars]){ // Fail(Destroy)
        currentStars=0;
        consecutiveFails=0;
        numDestroy[i]++;
      }
      else{ // Fail(Drop)
        if(currentStars>0){consecutiveFails++;currentStars--;}
      }
      numTries[i]++;
    }
    currentStars=a;
  }

  for(int i=0;i<equipNum;i++){averageNumTries+=numTries[i];averageNumDestroy+=numDestroy[i];}
  averageNumTries/=equipNum;
  averageNumDestroy/=equipNum;
  averagecost = averageNumTries * 55832200;

  std::cout << "Average Total Cost to go from " << a << "stars to " << desiredStars << ": " << std::setprecision(12) << std::setw(24) << averagecost << " mesos\n";
  std::cout << "Average Number of tries to go from " << a << "stars to " << desiredStars << ": " << std::setprecision(10) << std::setw(24) << averageNumTries << "\n";
  std::cout << "Average Number of times destroyed: " << std::setprecision(10) << std::setw(24) << averageNumDestroy;
  std::cin >> a; 
  
  return 0;
}


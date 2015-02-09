//v1.0.3
#include <cstdio> 
#include <cstdlib>
#include <cmath>
using namespace std;
int main()
{
  double tokens=0, banking=0, conquest=0, guilded_chests=0, midas_touch=0,  force_multiply=0, train_heros=0, level=0;

  //****************************************************************************
  //***Enter your current levels here. Leave the semicolons after each number***
  //****************************************************************************

  tokens=497000;
  force_multiply=539;
  banking=1414;
  conquest=1411;
  train_heros=1951000;
  guilded_chests=1409;
  midas_touch=1401;
  level=2300; // <-----This is the level you reached on your last run.
  //****************************************************************************
  //***********All maxable upgrades are assumed to already be maxed.************
  //****************************************************************************
  //***********As always, leave the rest of the stuff below unchaged.***********
  //****************************************************************************
  // This is designed as a much later game calculator for TTI. It was built  ***
  // after extensively using Myuron's calculator with the goal of providing a***
  // more accurate way to measure force multiply and to use a language more  ***
  // suitable for the amount of calculations necessary late game. Full credit***
  // is due to Myuron for his methods which this program largely copies.     ***
  // Feel free to modify/download/upload/reload/unload/motherload  this      ***
  // program for your own use. Report bugs / comments / questions to pzratnog***
  //****************************************************************************
  
  double fm_r=1/((force_multiply+200)*(pow(force_multiply+1, 1.6)));
  double bank_r=15/((15*banking+100)*(banking+1));
  double con_r=15/((15*conquest+100)*(conquest+1));
  double th_r=1/(train_heros+100);
  double gc_r=25/((25*guilded_chests+100)*(guilded_chests+1));
  double mt_r=5/((5*midas_touch+100)*(midas_touch+1));
  
  //****************************************************************************
  //**************BEHOLD, THE ALL IMPORTANT SCALING FACTOR**********************
  //****************************************************************************
  double the_all_important_scaling_factor=1.0;
  //****************************************************************************
  //******NOW THAT YOU HAVE BEHELD THE ALL IMPORTANT SCALING FACTOR, YOU********
  //******MAY NEVER EVER EVER BLINK AGAIN...EVER! LIKE...NEVER. AGAIN. K!*******
  //****************************************************************************
  double expected_tokens=0.0, further_tokens=0.0, high_val=0.0;
  int high_num=0;
  for (double i=30; i<=level; i+=5)
  {
      expected_tokens+=ceil(pow((i-30.0)/25.0,1.1)*(force_multiply+100.0)/100.0);
  }
  further_tokens=expected_tokens;
  for (double i=level+5; i<=(level+50); i+=5)
  {
    further_tokens+=ceil(pow(((i)-30.0)/25.0,1.1)*(force_multiply+100.0)/100.0);
  }
  the_all_important_scaling_factor=(further_tokens-expected_tokens)/(expected_tokens);
  fm_r=fm_r/(the_all_important_scaling_factor);
  while (tokens > 0 )
  {
    high_val=0.0;
    high_num=0;
    if ( high_val<fm_r && (pow(force_multiply+1, 1.6))<=tokens)
    {
       high_num=1;
       high_val=fm_r;
    }   
    if (high_val<bank_r && banking<tokens)
    {
       high_num=2;
       high_val=bank_r;
    }
    if (high_val<con_r && conquest<tokens)
    {
       high_num=3;
       high_val=con_r;
    }
    if (high_val<th_r)
    {
       high_val=th_r;
       high_num=4;
    }
    if (high_val<gc_r && guilded_chests<tokens)
    {
       high_val=gc_r;
       high_num=5;
    }
    if (high_val<mt_r && midas_touch<tokens)
    {
       high_val=mt_r;
       high_num=6;
    }
    
    if (high_num==1)
    {
      force_multiply++;
      tokens-=pow(force_multiply, 1.6);
      fm_r=1/((force_multiply+200)*(pow(force_multiply+1, 1.6)));
      fm_r=fm_r/the_all_important_scaling_factor;
    }
    else if (high_num==2)
    {
      banking++;
      tokens-=banking;
      bank_r=15/((15*banking+100)*(banking+1));
    }
    else if (high_num==3)
    {
      conquest++;
      tokens-=conquest;
      con_r=15/((15*conquest+100)*(conquest+1));
    }  
    else if (high_num==4)
    {
      train_heros++;
      tokens--;
      th_r=1/(train_heros+100);
    }
    else if (high_num==5)
    {
      guilded_chests++;
      tokens-=guilded_chests;
      gc_r=25/((25*guilded_chests+100)*(guilded_chests+1));
    }
    else
    {
      midas_touch++;
      tokens-=midas_touch;
      mt_r=5/((5*midas_touch+100)*(midas_touch+1));
    }  
  }
  printf("tokens=0;\nforce_multiply=%.0f;\nbanking=%.0f;\nconquest=%.0f;\ntrain_heros=%.0f;\nguilded_chests=%.0f;\nmidas_touch=%.0f;\n",force_multiply,banking,conquest,train_heros,guilded_chests,midas_touch);
  return 0;
}
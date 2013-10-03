#include <iostream>
#include <vector>

using namespace std;

int main()
{
   int num_scores = 2;
   vector<int> scores(num_scores);
   scores[0] = 100;
   scores[1] = 200;
   for (int i = 0; i <= num_scores; i++)
   {
      cout << "scores [" << i << "] = " << scores[i] << endl;
   }
   
   return 0;
}

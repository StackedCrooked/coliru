#include <vector>
#include <iostream>

using namespace std;


class Solution {
public:

   void swap(vector<int> &num, const int& i, const int& j)
   {
      int tmp = num[i];
      num[i] = num[j];
      num[j] = tmp;
   }

   void reverse(vector<int> &num, int i, int j)
   {
      while(i != j)
      {
         int tmp = num[i];
         num[i] = num[j];
         num[j] = tmp;
         if ( ++i == j) break;
         --j;
      }
   }


   void nextPermutation(vector<int> &num)
   {
      //num[1,3,2]
      //
      //pivot
      //if num[pivot] < num
      int size_ = num.size();

      int i = 0;
      for(i = size_ - 1; i != 0 && num[i - 1] >= num[i] ; --i);

      if (i == 0)
      {
         reverse(num, i, size_ - 1);
         return;
      }

      /*cout << "i : " << i << endl;*/

      int j = 0;
      for(j = size_ - 1; num[i - 1] >= num[j] ; --j );

      /*cout << "j : " << j << endl;*/

      swap(num, i-1, j);

      reverse(num, i, size_ - 1);

   }


};

int main()
{
   std::vector<int> input{1,1};
   Solution sol;
   sol.nextPermutation(input);

   for(auto i : input)
   {
      cout << i << " ";
   }

}

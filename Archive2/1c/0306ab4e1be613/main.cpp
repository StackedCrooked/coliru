#include <iostream>
#include <vector>
using namespace std;
void sum(int&p, int n, vector<int> d)
{
  p = 0;
  for(int i = 0; i < n; ++i)
     p = p + d.at(i);
    cout<<p;
}
int main()
{
   
   int accum = 0;
   const int N = 40;
   std::vector<int> vector_from_array(N, 0) ;
   for(int i = 0; i < N; ++i)
   {
    	vector_from_array.push_back(i);
        }
		

    sum(accum, N, vector_from_array);
    cout<<"sum is \n"<< accum;
	return 0;
}
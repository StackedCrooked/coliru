#include<iostream>
#include<string>
#include<vector>

using namespace std;

class BrightLamps{
    public:
    static int maxBrightness(string init, vector<int> a, int K)
    {
        int currBright;
        int maxBright;
        vector<int> initial; 
        int size = init.size();
        for ( int m=0; m<size; m++)
        {
          initial[m] = (int)init[m] - 48;
        }
        int flag = 0; /*max state not reached as yet*/
        while(flag==0)
        {
            flag = 1;
            for(int i=0; i<size; i++)
            {
                if(initial[i]==0)
                {
                    for(int j=max(0,i-K+1); j <= min(i,size-1-K); j++)
                    {
                        currBright = 0;
                        maxBright = 0;
                        for(int k=j; k<j+K; k++)
                        {
                            currBright += initial[k]*a[k];
                            maxBright += a[k];
                        }
                        if(currBright < maxBright - currBright)
                        {
                            flag = 0;
                            for(int k=j; k<j+K; k++)
                            {
                                initial[k] = 1-initial[k]; 
                            } 
                        }
                    }
                }
            }
            
        }
        currBright=0;
        for(int i=0; i<size; i++)
        {
            currBright += initial[i]*a[i];
        }
            
        return currBright;
    }
};

int main()
{
    cout << BrightLamps::maxBrightness("0010000001",{8, 3, 10, 8, 3, 7, 4, 6, 3, 10},4) << "\n";
    return 1;
}
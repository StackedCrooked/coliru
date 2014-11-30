#include <iostream>

const size_t Dimx = 4;

const size_t Dimy = 2;

void Zada4a(const unsigned int (&arr)[Dimy][Dimx], unsigned int (&result)[Dimy])
{
    if(!Dimx || !Dimy) return;
    
    for(size_t i(0); i < Dimy; ++i)
    {
        unsigned int iMostOccured;
        
        unsigned int iMostOccuredTimes = 0;
        
        for(size_t j(0); j < Dimx; ++j)
        {
            unsigned int Tmp = arr[i][j];
            
            unsigned int TimesTmp = 1;
            
            for(size_t j1(j + 1); j1 < Dimx; ++j1)
                if(arr[i][j1] == Tmp)
                    ++TimesTmp;
            
            if(TimesTmp > iMostOccuredTimes)
            {
                iMostOccured = Tmp;
                iMostOccuredTimes = TimesTmp;
            }
        }
        
        result[i] = iMostOccured;
    }
}

using namespace std;

int main()
{
    unsigned int arr[Dimy][Dimx] { { 1, 22, 22, 3 },
                          { 24, 22, 24, 3 } }  ;
    
    unsigned int arrRes[Dimy] ;
    
    Zada4a(arr, arrRes);
    
    for(size_t i(0); i < Dimy; ++i)
        cout << arrRes[i] << endl;
}
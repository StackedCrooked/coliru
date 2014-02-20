
#include <iostream>
using namespace std ;

void Merge(int first[],int second[],int f_length,int s_length){
     int total_length=f_length+s_length;
     int f_count=0;
     int s_count=0;
     int result[total_length];
     for(int i=0;i<total_length;i++){
            if(first[f_count]<second[s_count] && f_count<f_length)
                result[i]=first[f_count++];
            else
                 result[i]=second[s_count++];
             }
     for(int i=0;i<total_length;i++)
             cout<<result[i]<<endl;
     }
     
     int main()
     {
     }
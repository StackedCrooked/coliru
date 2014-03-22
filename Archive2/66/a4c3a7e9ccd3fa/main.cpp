#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

#include <iostream>

using namespace std;

int main()
{

   //int postuer[1000]={1};
   
   int postuer[1000];
   
   for(int i=1;i<=1000;i++){
       postuer[i] = {1};
   }
   
   int schueler = 0;
   int tueren = 0;
   
   for(schueler=1;schueler<=1000;schueler++){
       
       for(tueren=schueler;tueren<=1000;tueren=tueren+schueler){
           
           if(postuer[tueren]==1){
               postuer[tueren]=0;
           }
           else if(postuer[tueren]==0){
               postuer[tueren]=1;
           }

       }
       
   }
   
   for(int i=1;i<=1000;i++){
       cout << "Tuer " << i << " = " << postuer[i] << "\n";
   }
   
   
   return 0;
}
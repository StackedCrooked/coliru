
#include <cstdio> 
#include <algorithm> 
#include <iterator> 
int main() 
{ 
int a; 
scanf("%d",&a); 
int b[a]; 
for(int i = 0; i < a;i++) 
{ 
scanf("%d",&b[i]); 
} 
std::sort(std::begin(b), std::end(b)); 
printf("%d",b[0]); 
return 0; 
}
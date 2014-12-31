#include <stdio.h>
#include <string>
#include <iostream>
using namespace std; 

int main()

{
    int count, age, highage=0;
    string name,highname;
    for(count=0;count<=9;count++)
        {
            printf ("Enter name:\ ");
            //cin.getline (name,128);
            getline(cin, name);
            printf("Enter Your Age (as a numeral) \n");
            scanf("%d",&age);
            if ( age >= highage)
                    {
                        highage=age;
                        highname=name);
                    } 
}                          
                  //highname=name;
    printf("The Oldest Person is",highname);                     
    
    
    getchar();    
    getchar();
    return 0;

}
    

//*scanf("%s",&name);
     
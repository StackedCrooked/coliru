#include <iostream>

using namespace std;
void arrayCopy(int *a1, int *a2){
    if(*a1=='\0')
        return;
    else{
        *a2=*a1;
        arrayCopy(a1++, a2++);
    }
}

int main()
{
   
    int array1[]={2,5,6,4,1};
    int array2[]={0,0,0,0,0};

    arrayCopy(&array1[0], &array2[0]);

    cout<<"Elements of array1: ";
    for(int a=0;array1[a]!='\0';a++)
        cout<<array1[a] << " ";

    cout<<endl<<"Elements of array2: ";
    for(int a=0;array2[a]!='\0';a++)
        cout<<array2[a] << " ";
   
   return 0;
}

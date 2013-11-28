#include <iostream>
//#include <conio.h>

using namespace std;

void new_vector(double* v[], int n);

void delete_vector(double* v[]);

int main () {
    
    double * my_pointer;

    new_vector(&my_pointer, 5);
    
    for (int i = 0; i < 5; ++i)
    {
        std::cout << my_pointer[i] << std::endl;
    }
    
    delete_vector(&my_pointer);

    return 0;
}


void new_vector(double* v[], int n)
{
    *v = new double[n];
    
    for(int i=0; i<n; i++){
           cout<<"enter vector value:\n";
           //cin>> (*v)[i];
           (*v)[i] = i;  // these two lines here were only changed for testing.
     }

    return;
}

void delete_vector(double* v[]) {

    if( *v != NULL ) {
        delete *v;
        *v = NULL;
    }
    else {
        cout << "\nError";
    }

}
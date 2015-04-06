/* Write compile and run a C++ program that finds and display the maximum values
of a two-dimensional array of integers. The array should be declared as a 4 x 5
array of integers and initialized with the data: 16,22,99,4,18,-258,4,101,5,98,
105,6,15,2,45,33,88,72,16,and 3.

b. Modify the program written in the exercise so that is also displays the maximum 
value's row and column subscripts values.
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    
        int array[4][5] =  {{16,22,99,4},{18,-258,4,101},{5,98,105,6},{15,2,45,33},{88,72,16,3};
    
   	    int i,j;
	    int max = 0;

		for(i=0;i<4;i++){

			for(j=0;j<5;j++){

			if array[i][j]>max;}

			max = array [i][j];
}
}

			cout << "The maximun of the 4x5 array is: " << max << endl;
} 	            
            
            cin.ignore(2);
            
            return 0;
    
}

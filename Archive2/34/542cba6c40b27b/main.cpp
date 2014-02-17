// Resizing vectors using .push_back in order to correctly add/subtract vectors with all values accounted for
// Author: !ixAlastor~
// Referenced: http://www.cplusplus.com/reference/vector/vector/push_back/
// Also, I know this is the hard way, but noko gave me the page and implied this was the only way
// so I spent about a good 2 hours working on this. It was stressful but enjoyable nonetheless.
#include <iostream>
#include <vector>
using namespace std;

int main (){
    int myint;
    vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8}; //We make it so that the length of this vector is 8
    vector<int> v2{1, 2, 3, 4, 5}; // and we make the length of this vector five
    //oh no! whatever shall I do!?!?!
    const size_t s1{v1.size()}; //all right, so we are gonna make
    const size_t s2{v2.size()}; //two variables to record the sizes of each one
    if(s1 > s1){ //This statement says that if the length of v1 is greater than the length of v2
        myint = s1 - s2; //myint will now be the difference between the largest and smallest sizes
        for(int idk = 0; idk < myint; idk++)
            v1.push_back(0); 
            //This loop states that it will add a new value in the smallest vector as many times
            //as there are more vectors in the largest.
    }
    else {
        myint = s1 - s2; //myint will now be the difference between the largest and smallest sizes
        for(int idk = 0; idk < myint; idk++)
            v2.push_back(0); 
            //This loop states that it will add a new value in the smallest vector as many times
            //as there are more vectors in the largest.
    } 
    cout << "V1 equals " << v1.size() << "\nV2 Equals " << v2.size() << "\nmyint equals  " << myint << endl;
    //This is just to print the new sizes for v1 and v2, and to tell you what was the size difference
    const size_t sz{v1.size()};
    //This shall make the variable sz based on the size of v1 or v1
    //It doesn't matter what you pick since they are now the same length.
    vector<int> datsumdoe(sz); 
    for(size_t idy = 0; idy < sz; ++idy){ //This is to add all the vectors together accordingly
        datsumdoe[idy] = v1[idy] + v2[idy]; //making sure every value is accounted for.
        cout << datsumdoe[idy] << endl;} 
} //Tada!~
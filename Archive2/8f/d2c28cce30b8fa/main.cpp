// Ensure two vector<ints> are equivalent sizes, and add them together.
// Author: LLD!5DeRpYLOvE
// Respin of: http://coliru.stacked-crooked.com/a/34542cba6c40b27b
#include <iostream>
#include <vector>
using namespace std;

int main (){
    int sizediff{0}; // Always good developer form to immediately initialize a variable.
    
    //*** EDIT *** // What if it was the FIRST vector that was shorter instead?
    // OH NOES!! :O
    vector<int> v1{20, 30, 90, 2, 42};          // First vector v1 is smaller in length (5).
    vector<int> v2{1, 2, 3, 4, 5, 6, 7, 0};     // Second vector v2 is larger in length (8).
    
    const size_t s1{v1.size()};
    const size_t s2{v2.size()};
    
    cout << "Original sizes:\n V1 equals " << s1 << "\n V2 Equals " << s2 << endl;    
    
    // First case: v1 is bigger.
    if(s1 > s2) { //This test statement says that if the length of v1 is greater than the length of v2
        sizediff = s1 - s2; //sizediff will now be the difference between the first and second vector sizes
        
        //This loop states that it will add a new value onto the smallest vector for as many times
        //as there are more elements inside the largest vector.
        for(int idk = 0; idk < sizediff; idk++)
            //*** EDIT *** // Let's push_back on v2 which would be shorter in this case.
            v2.push_back(0); 
    }
    
    //*** EDIT *** // What if the vectors are equal in length?
    // So, let's make this code block a second case test instance here instead.
    // Second case: v2 is bigger.    
    else 
    if(s2 > s1) { // This test statement checks if the length of vector 2 is greater than the lengeth of vector 1.
        //*** EDIT *** // Let's swap the subtraction around, so we don't wind up getting a negative number.
        sizediff = s2 - s1; //myint will now be the difference between the second and first vector sizes
        
        //This loop states that it will add a new value onto the smallest vector for as many times
        //as there are more elements inside the largest vector.
        for(int idk = 0; idk < sizediff; idk++)
            //*** EDIT *** // Let's push_back on v1 which would be shorter in this case.
            v1.push_back(0); 
    } 
    //*** EDIT *** // For this third case, the vectors are equivalent in length.
    // Third case: equivalent sizes.
    else
        sizediff = 0;
    
    cout << "New sizes:\n V1 equals " << v1.size() << "\n V2 Equals " << v2.size() << "\n sizediff equals  " << sizediff << endl;
    
    //This is just to print the new sizes for v1 and v2, and to tell you what was the size difference
    const size_t sz{v1.size()};
    //This shall make the variable sz based on the size of v1 or v1
    //It doesn't matter what you pick since they are now the same length.
    vector<int> datsumdoe(sz); 
    for(size_t idy = 0; idy < sz; ++idy){ //This is to add all the vectors together accordingly
        datsumdoe[idy] = v1[idy] + v2[idy]; //making sure every value is accounted for.
        cout << datsumdoe[idy] << endl;} 
} //Tada!~
// Outer/Inner block scopes examples + simplified declarations and vector addition with unevenly sized vectors
// Author: !ixAlastor2 ‮❤✨~oht omoh on srS~✨❤‮‭‭
// Derived from: http://coliru.stacked-crooked.com/a/92c40af6be155c73
// Referenced: http://www.cplusplus.com/reference/vector/vector/push_back/
// Also, I know this is the hard way, but noko gave me the page and implied this was the only way
// so I spent about a good 2 hours working on this. It was stressful but enjoyable nonetheless.
// The entire code in general took me the entire day to do. It was good practice and well worth it~
#include <iostream>
#include <vector>
#include <string>
using namespace std; //used the namespace thing so that I don't have to declare allll thooooseee vaaarrrsss

int main() //vital for the entire thing to work~ 
{
    int x{10}, y{20};
    int A{x*y};
    cout << "\n\nOriginal outer scope values: \n" << "x: " << x << "\ny: " << y << "\nA: " << A << endl;
    //So in this one I decided to expirement with shortening my declarations
    //Turns out you can easily declare all the variables ya need with only one line! 
    //So I figured why not exploit such a time/line saver :3c
    //>tfw no more 20 lines of declaring integer variables.
    {
        int x{42}, y{77}; 
        int A{x*y};
        cout << "\nInner block scope values: \n" << "x: " << x << "\ny: " << y << "\nA: " << A << endl;
        //same exact thing as the former, however with x and y being in the inner block
        //to remain unaffected by the declarations in lines 12-14
        {
            // I decided to mess around with it even further
            // and go back to some of the stuff I originally learned
            vector<string> K{"\nC++ ", "also ", "how "}, 
            Y{"is ", "I ", "to "}, 
            P{"getting ", "finally ", "stream "}, 
            L{"pretty ", "figured ", "and"}, 
            S{"easy.", "out", " such \n"}, 
            Kden(3);
            /*Turns out just like you can simplify your declarations with similar type variables
            so in this case, they were all strings so I decided to only use on declaration to create
            a complex statement*/
            for(int idk = 0; idk < 3; ++idk){
                Kden[idk] = K[idk] +Y[idk] +P[idk] +L[idk] +S[idk];
                cout << Kden[idk] << endl;
            }
        }
    }//I decided instead of doing a final outer scope thing, to go back to integer array addition
    // declaring sz and datsumdoe was kind of tricky at first because it wasn't something I looked at with depth
    // originally, however I kind of get it, I must work on it further
    int myint;
    vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8}; //We make it so that the length of this vector is 8
    vector<int> v2{1, 2, 3, 4, 5}; // and we make the length of this vector five
    //oh no! whatever shall I do!?!?!
    const size_t s1{v1.size()}; //all right, so we are gonna make
    const size_t s2{v2.size()}; //two variables to record the sizes of each one
    if(s1 > s2){ //This statement says that if the length of v1 is greater than the length of v2
        myint = s1 - s2; //myint will now be the difference between the largest and smallest sizes
        for(int idk = 0; idk < myint; idk++)
            v2.push_back(0); 
            //This loop states that it will add a new value in the smallest vector as many times
            //as there are more vectors in the largest.
    }
    else {
        myint = s2 - s1; //myint will now be the difference between the largest and smallest sizes
        for(int idk = 0; idk < myint; idk++)
            v1.push_back(0); 
            //This loop states that it will add a new value in the smallest vector as many times
            //as there are more vectors in the largest.
    } 
    cout << "V1 equals " << v1.size() << "\nV2 Equals " << v2.size() << "\nmyint equals " << myint << "\n\nWhen added up, the vectors equal: " << endl;
    //This is just to print the new sizes for v1 and v2, and to tell you what was the size difference
    const size_t sz{v1.size()};
    //This shall make the variable sz based on the size of v1 or v1
    //It doesn't matter what you pick since they are now the same length.
    vector<int> datsumdoe(sz); 
    for(size_t idy = 0; idy < sz; ++idy) //This is to add all the vectors together accordingly
    {
        datsumdoe[idy] = v1[idy] + v2[idy]; //making sure every value is accounted for.
        cout << datsumdoe[idy] << endl;
    }
}
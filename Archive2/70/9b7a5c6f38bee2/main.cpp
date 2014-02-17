// Outer/Inner block scopes examples + simplified declarations and vector addition.
// Author: !ixAlastor2 ‮❤✨~oht omoh on srS~✨❤‮‭‭
// Derived from: http://coliru.stacked-crooked.com/a/92c40af6be155c73
#include <iostream>
#include <vector>
#include <string>
using namespace std; //used the namespace thing so that I don't have to declare allll thooooseee vaaarrrsss

int main() //vital for the entire thing to work~ 
{
    int x{10}, y{20};
    int A{x*y};
    cout << "\nOriginal outer scope values: \n" << "x: " << x << "\ny: " << y << "\nA: " << A << endl;
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
            vector<string> K{"\nC++ ", "also ", "how "}, Y{"is ", "I ", "to "}, P{"getting ", "finally ", "stream "}, L{"pretty ", "figured ", "and"}, S{"easy.", "out", " such \n"}, Kden(3);
            /*The purpose of line 27 was just to expirement with complex statements.
            Obviously this is bad because it makes reading the code harder, which is why you should use your Whitespace to
            your advantage to make it easier to read! */
            for(int idk = 0; idk < 3; ++idk){
                Kden[idk] = K[idk] +Y[idk] +P[idk] +L[idk] +S[idk];
                cout << Kden[idk] << endl;
            }
        }
    }//I decided instead of doing a final outer scope thing, to go back to integer array addition
    // declaring sz and datsumdoe was kind of tricky at first because it wasn't something I looked at with depth
    // originally, however I kind of get it, I must work on it further
    vector<int> v1{1, 2, 3, 4, 5};
    vector<int> v2{5, 4, 3, 2, 1};
    const size_t sz{v1.size()};
    //ya, ya, I know, I was determining the size based only on v1, which meant I could change
    //the length of v2 and it would not even recognize it. oh well~
    //I just don't really know who ask for v1&&v1 or eh, v1||v2 even.
    vector<int> datsumdoe(sz);
    for(size_t idy = 0; idy < sz; ++idy){
        datsumdoe[idy] = v1[idy] + v2[idy];
        cout << datsumdoe[idy] << endl;
    }
}
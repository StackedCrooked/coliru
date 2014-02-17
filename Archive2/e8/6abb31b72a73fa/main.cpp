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
    cout << "\n Original outer scope values: \n";
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
    cout << "A: " << A << endl;
    //So in this one I decided to expirement with shortening my declarations
    //Turns out you can easily declare all the variables ya need with only one line! 
    //So I figured why not exploit such a time/line saver :3c
    //>tfw no more 20 lines of declaring integer variables.
    {
        int x{42}, y{77}; 
        int A{x*y};
        cout << "\n Inner block scope values: \n";
        cout << "x: " << x << endl;
        cout << "y: " << y << endl;
        cout << "A: " << A << endl;
        //same exact thing as the former, however with x and y being in the inner block
        //to remain unaffected by the declarations in lines 12-14
        {
            // I decided to mess around with it even further
            // and go back to some of the stuff I originally learned
            vector<string> K{"\nC++ ", "also ", "how "};
            vector<string> Y{"is ", "I ", "to "};
            vector<string> P{"getting ", "Finally ", "stream "};
            vector<string> L{"pretty ", "figured ", "and"};
            vector<string> S{"easy.", "out", " such \n"};
            vector<string> Kden(3);
            
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
    for(size_t idy = 0; idy < sz; ++idy)
        datsumdoe[idy] = v1[idy] + v2[idy];
    for(size_t idy{0}; idy < sz; ++idy) 
        cout << datsumdoe[idy] << endl;
    /* So uh, I kept getting an error saying
    >main.cpp:53:27: error: use of undeclared identifier 'idy'
    so I split it into two for loops, and uh, it ended up working.
    I'm not exactly sure what I did wrong for that, but hey, I got it working anyways! */
}
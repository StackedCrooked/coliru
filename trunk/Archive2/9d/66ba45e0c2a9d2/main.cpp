#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

void my_pi_func(int term);

int main()
{
    int term;


    cout << fixed << setprecision(12); // set digits after decimal to 12         
    
    while (cin >> term){
        my_pi_func(term);
    }

    return 0;

}

void my_pi_func(int term)
{
    double leibniz = 0.0; // pi value calculated from Leibniz                     
    double counter = 0.0; // starting value                                       
    double eulerall = 0.0; // value calculated from Euler (all integers)          
    double eulerodd = 0.0; // value calculated from Euler (odds)                  
    double eulerallans; // pi value calculated from Euler series (all integers)   
    double euleroddans; // pi value calculated from Euler series (odd integers)   
    
    while(term > counter){
    leibniz = 4*(pow(-1, counter)) / (2*counter+1) + leibniz;
    eulerall = (1/pow(counter+1,2)) + eulerall;
    eulerodd = (pow(-1, counter)) / (pow(2*counter + 1, 3)) + eulerodd;
    counter++;
    eulerallans = sqrt(eulerall*6);
    euleroddans =  pow(32*eulerodd, 1.0/3.0);
    }
    cout << right << setw(14) << "# TERMS" << setw(15) << "LEIBINZ" << setw(15)
    << "EULER-ALL" << setw(15) << "EULER-ODD" << endl;
    cout << right << setw(14) << term << " " << leibniz << " " << eulerallans 
    << " " << euleroddans <<endl;
    
    if (term < 0){
        cout << "Negative value read" << endl;
    }
}
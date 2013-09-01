#include <iostream>
#include <math.h>
#include <string>
using namespace std;

struct fraction {
    int numerator;
    int denominator;
    int whole;
};

// converts a string of chars to int
int charsToInt(const char *first){
    bool neg = false;
    if(*first == '-') { 
		neg = true;
		first++;
	}

	int num = 0;
	while (isdigit(*first)) {
		num = num*10 + (*first++ - '0'); //increment digit place, add next ascii value offset by the ascii value of 0.
	}
    
    return neg ? -num : num;
}


// takes a fraction and changes its numerator and denominator values
// based on a common factor. The loop constantly checks using the
// isDivisible function for common factors to divide by.
fraction simplifier(fraction frac){

    while(frac.numerator >= frac.denominator) {  //reduce fractions such as 10/3 to 3 and 1/3.  
		frac.numerator = frac.numerator - frac.denominator;
		frac.whole++;
	}

	//simplify fraction is a PITA.  I've had to do this in a course.
	for(int i = frac.denominator / 2; i > 1; i--) {
		if((frac.denominator % i) == 0 && (frac.numerator % i) == 0) {
			frac.denominator = frac.denominator / i;
			frac.numerator = frac.numerator / i;
			break;
		}
	}


    return frac;
}


// this function takes the string and splits it into a numerator
// and denominator in the loop, then creates a fraction struct to return
fraction separator(string *s){
	cout << "I'm in separator!\n";
    //string theString = *s; //not useful to restore the variable.

	//Init the fract to be 0.  0 and 0/1.  
	fraction Made;
	Made.denominator = 1;
	Made.numerator = 0;
	Made.whole = 0;

    std::size_t token = s->find("/");
	if(token == string::npos) {
		Made.whole = charsToInt((*s).c_str());
		return Made;
	}

	Made.numerator = charsToInt((*s).substr(0,token).c_str());									//*s is 10/2  , token is 2, so I take the substring from 0 with length token.  This means I get 10.
	Made.denominator = charsToInt((*s).substr(token+1,(*s).length()-(token+1)).c_str());		//token is 2, so take from space 3 to the end of the string.

    return Made;
}


int main (){

    std::cout << "Please enter a fraction (#/#): ";
    string theResponse;
    cin >> theResponse;
    cout << "\nWorking...\n" << endl;
    fraction frac = separator(&theResponse);
    fraction final = simplifier(frac);
    std::cout << final.whole << " " << final.numerator << "/" << final.denominator;

    return 0;
}
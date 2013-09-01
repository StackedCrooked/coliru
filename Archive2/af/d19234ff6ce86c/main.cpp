

//int main(int argc, char* argv[]) {
//    return 0;
//}


#include <stdio.h>
#include <iostream>
#include <math.h>
#include <sstream>
using namespace std;

struct fraction {
    int numerator;
    int denominator;
    int whole;
};

// finds the size of a string
int size(char *ptr) {
    int offset = 0;
    int count = 0;

    while (*(ptr + offset) != '\0')
    {
        ++count;
        ++offset;
    }
    return count;
}

// converts a string of chars to int
int charToInt(char *first){
    int number = 0;
    int tensHolder = 1;
    int numSize = size(first);
    first += (numSize - 1);
    for (int j = numSize - 1; j >= 0; --j){
        if (*first=='1'){
            number += 1*(tensHolder);
        } else if (*first=='2'){
            number += 2*(tensHolder);
        } else if (*first=='3'){
            number += 3*(tensHolder);
        } else if (*first=='4'){
            number += 4*(tensHolder);
        } else if (*first=='5'){
            number += 5*(tensHolder);
        } else if (*first=='6'){
            number += 6*(tensHolder);
        } else if (*first=='7'){
            number += 7*(tensHolder);
        } else if (*first=='8'){
            number += 8*(tensHolder);
        } else if (*first=='9'){
            number += 9*(tensHolder);
        } else if (*first=='0'){
            number += 0*(tensHolder);
        }
        tensHolder *= 10;
        --first;
    }

    return number;
}


// takes a fraction and check to see if the numerator>denominator then
// gives it a whole number value
fraction wholeNumber(fraction frac){
    if ((frac.numerator) > (frac.denominator)){
        double w = (((double) (frac.numerator)) / ((double) (frac.denominator)));
        int whole = floor(w);
        fraction now = { (frac.numerator) - whole*(frac.denominator),
                (frac.denominator), whole};
        return now;
    } else {
        frac.whole = 0;
    }

    return frac;
}

// checks to see if a numerator and denominator are both divisible
// by a number from the toCheck array
int isDivisible(fraction frac){
    int toCheck[6] = {2,3,5,7,11,13};
	double newNum = (double) frac.numerator;
    double newDen = (double) frac.denominator;
    for(int i = 0; i < 6; ++i){
        if (( (newNum / toCheck[i]) == (frac.numerator / toCheck[i]) ) ? true : false &&
                ((newDen / toCheck[i]) == (frac.numerator / toCheck[i]) ) ? true : false)
            return toCheck[i];
    }
    return 0;
}

// takes a fraction and changes its numerator and denominator values
// based on a common factor. The loop constantly checks using the
// isDivisible function for common factors to divide by.
fraction simplifier(fraction frac){
    frac = wholeNumber(frac);
    while(isDivisible(frac) != 0){
        int factor = isDivisible(frac);
        frac.numerator = frac.numerator / factor;
        frac.denominator = frac.denominator / factor;
    }

    return frac;
}

const char realNumbers[] = {'1','2','3','4','5','6','7','8','9','0'};

// this fuction confirms that a char is a number
bool isNumber(char *c){
    for (int i = 0; i < 10; ++i){
        if (*c == realNumbers[i])
            return true;
        else
            continue;
    }
    return false;
}

// this function takes the string and splits it into a numerator
// and denominator in the loop, then creates a fraction struct to return
fraction separator(string *s){
    cout << "I'm in separator!\n";
    string theString = *s;
    int placeHolder = 0;
    string numerator; numerator.reserve(50);
    string denominator; denominator.reserve(50);
    int numHold = 0;
    int denHold = 0;
    for (int i = 0; i < size(&theString[0]); ++i){
        if (isNumber(&theString[i]) && (placeHolder == 0)){
            numerator[numHold] = theString[i];
            ++numHold;
        } else if (isNumber(&theString[i]) && (placeHolder != 0)){
            denominator[denHold] = theString[i];
            ++denHold;
        } else {
            ++placeHolder;
        }
    }
    cout << "I'm out of the loop!\n";
    fraction now = {charToInt(&numerator[0]), charToInt(&denominator[0])};
    return now;
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
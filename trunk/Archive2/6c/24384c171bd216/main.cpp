/*
 * Write a program that takes as its first argument one of the words ‘sum,’ ‘product,’ ‘mean,’ or ‘sqrt’  and for further arguments a series of numbers. 
 * The program applies the appropriate function to  the series. 
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

// Prototypes
double sum(int argc, char* argv[]);
double product(int argc, char* argv[]);
double mean(int argc, char* argv[]);


int main(int argc, char* argv[])
{
    //nullptr = "\0";	
	/*
	for(int i = 0; i < argc; i++){
		cout << argv[i] << endl;
	}
	*/
	double return_value;
	if(argc == 3)
    {
		//This means we're in sqrt, as we don't support sqrt of > 1 number
		//Nor sum, product, etc of less than one. 'cause that's dumb

		double operand;
		operand = strtod(argv[2],nullptr);
		return_value = sqrt(operand);

	}
	else
    {   
		if(strcmp(argv[1],"sum") == 0)
		{
            return_value = sum(argc, argv);
            cout <<return_value<<endl;
		}
		if(strcmp(argv[1],"product") == 0)
        {
            cout << "I'm doing a product!";
            return_value = product(argc, argv);
		}
        if(strcmp(argv[1],"mean") == 0)
        {
            return_value = mean(argc, argv);
        }
	}

	cout << return_value << endl;
}


double sum(int argc, char* argv[])
{   
    
    for(int i = 0; i < argc; i++){
    cout << argv[i] << endl;}
    double return_value = 0.0;
    for(int i = 2; i < argc; i++)
    {
        cout << strtod(argv[i], nullptr) + 1.0 << endl;
        double x = strtod(argv[i], nullptr); 
        cout << x << endl;
        return_value += x;
        cout <<return_value<<endl;
    }
    return return_value;
}

double product(int argc, char* argv[])
{

    double return_value = 1;
    for(int i = 2; i < argc; i++)
    {
        return_value *= strtod(argv[i],nullptr);	
    }
    return return_value;
}

double mean(int argc, char* argv[])
{
    double summation = sum(argc, argv);
    return summation/(double) argc;
}
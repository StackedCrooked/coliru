// Include libraries

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<stdio.h>

    float square(float x);
    float absolutevalue(float x);

int main(void)
{
    printf("square root of 2 is %f\n", square(2));
    printf("square root of 3 is %f\n", square(3));
    printf("square root of 4 is %f\n", square(4));
    printf("square root of 5 is %f\n", square(5));

    return 0;
}

float square(float x)
{
    float epsilon = 0.0000001;
    float guess = 1;

    while (absolutevalue(guess*guess - x) >= epsilon) {
        guess = ((x/guess) + guess) / 2;
        printf("%f", guess);
    }

    return guess;
}

float absolutevalue(float x)
{
    if (x < 0)
        x = -x;

    return x;
}
#include <iostream>

int main() {
    long long term[100];
    long long firstTerm;
    long double secondTerm;
    long long exactValue;
    
    int i;
    
    term[1] = 1;
    term[2] = 1;
    exactValue = 0;
    
    int kth = 75;
    int nth = 3;
    
    do
    {
        firstTerm = term[nth - 1];
        secondTerm = term[nth - 2];
        term[nth] = (firstTerm + secondTerm);
    
        nth++;
    }
    while(nth < kth);
    
    for(i = 1; i < kth; i++)
    {
        if(term[i] % 3 == 0)
        {
            term[i] = term[i];
        }
        else
            term[i] = 0;
    
        exactValue = term[i] + exactValue;
    }
    
    std::cout << exactValue;
}
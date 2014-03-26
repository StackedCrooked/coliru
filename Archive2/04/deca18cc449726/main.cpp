//
//  main.cpp
//  002_UDLiteral
//
//  Created by Lukasz Ronka on 07/03/14.
//  Copyright (c) 2014 Lukasz Ronka. All rights reserved.
//

#include <iostream>

using namespace std;

int operator "" _bin (const char * literal_string)
{
    int value = 0;
    int idx = 0;
    while( literal_string[idx] != '\0')
    {
        value *=2;
        if(literal_string[idx] == '1')
            value += 1;
        idx++;
    }
    return value;
}

int main(int argc, const char * argv[])
{
    
    int val = 11111011110_bin;
    cout << val << endl;
    return 0;
}


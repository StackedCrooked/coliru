// http://stackoverflow.com/questions/28158716/how-can-i-template-a-function-to-return-a-vector-of-floats-ints-or-structs

#include<iostream>
#include<vector>
using std::vector;

struct test {
};

vector<float> doStuff(float input)
{
    vector<float> result(10);
    for(int i = 0; i < 10; i++)
        result[i] = 0.1*i;
    return result;
}

vector<int> doStuff(int input)
{
    vector<int> result(10);
    for(int i = 0; i < 10; i++)
        result[i] = i;
    return result;
}

vector<test> doStuff(test input)
{
    test t;
    vector<test> result(10);
    for(int i = 0; i < 10 ;i++)
        result[i] = t;
    return result;
}

int main(int argc, char** argv) {

    float input1 = 0.0;
    vector<float> result1 = doStuff(input1);
    int input2 = 0;
    vector<int> result2 = doStuff(input2);
    test input3;
    vector<test> result3 = doStuff(input3);

    return 0;
}
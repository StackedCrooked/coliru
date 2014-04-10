/*
http://stackoverflow.com/questions/22970764/counting-the-minimum-number-of-operations-needed-to-reach-a-certain-number/22970924#comment35076217_22970924
Have three integers, A, B and C.

Your calculator starts off with the number 1, and it must reach C. To do this, you can perform two operations:

Multiply your number by A (if the result has more than 4 digits, the result will be 1).
Divide your number by B (integer division).
You must return the minimum number of operations needed to reach C.

Also, your calculator only has four digits, so you can expect A, B and C input to be, at most, 9999.

Example:

A = 2, B = 3, C = 10

1*A = 2 
2*A = 4 
4*A = 8 
8*A = 16 
16/B = 5 
5*A = 10
So the result would be 6 steps.
*/

#include <iostream>
#include <deque>

int A, B, C;

std::deque<int> extract_path(int forwardposition, int backposition, int (&datum)[10000]) 
{
    std::deque<int> results;

    while(forwardposition != 1) {
        results.push_front(forwardposition);
        forwardposition = datum[forwardposition];
    }
    results.push_front(1);

    while(backposition != C) {
        results.push_back(backposition);
        backposition = -datum[backposition];
    }
    results.push_back(C);

    return results;
}

bool calc_forward(int (&datum)[10000], std::deque<int> &forward_todo, std::deque<int>& result) 
{
    if (forward_todo.empty()==false) {
        int position = forward_todo.front();
        forward_todo.pop_front();
        int mul = position*A;
        if (mul<=9999) {
            if (datum[mul] == 0) {
                datum[mul] = position;
                forward_todo.push_back(mul);
            } else if (datum[mul]<0) {
                result = extract_path(position, mul, datum);
                return true;
            }
        }
        int div = position/B;
        if (datum[div] == 0) {
            datum[div] = position;
            forward_todo.push_back(div);
        } else if (datum[div]<0) {
            result = extract_path(position, div, datum);
            return true;
        }
    }
    return false;
}

bool calc_backward(int (&datum)[10000], std::deque<int> &backward_todo, std::deque<int>& result) 
{
    if (backward_todo.empty()==false) {
        int position = backward_todo.front();
        backward_todo.pop_front();
        int mul = position/A;
        if (position%A==0) {
            if (datum[mul] == 0) {
                datum[mul] = -position;
                backward_todo.push_back(mul);
            } else if (datum[mul] > 0) {
                result = extract_path(position, mul, datum);
                return true;
            }
        }
        unsigned div0 = position*B;
        for(int i=0; i<B && div0+i<=9999; ++i) {
            unsigned div=div0+i;
            if (datum[div]==0) {
                datum[div] = -position;
                backward_todo.push_back(div);
            } else if (datum[div] > 0) {
                result = extract_path(position, mul, datum);
                return true;
            }
        }
    }
    return false;
}

void display_path(const std::deque<int>& result) {
    if (result.empty()) {
        std::cout << "No path possible\n";
        return;
    }
    for(unsigned i=0; i<result.size()-1; ++i) {
        if (result[i]*A == result[i+1])
            std::cout << result[i] << "*" << A << " = " << result[i+1] << "\n";
        else
            std::cout << result[i] << "/" << B << " = " << result[i+1] << "\n";
    }
}

int main()
{
    std::cout << "enter multiplier, divisor, and target: ";
    if (!(std::cin >> A >> B >> C))
    {
        std::cerr << "could not read multiplier, divisor, and target";
        return 1;
    }
    if (A>=9999 || B>=9999 || C>=9999)
    {
        std::cerr << "A, B, and C must all be less than 1000\n";
        return 1;
    }
    if (A<=1 || B<=1 || C<=1)
    {
        std::cerr << "A, B, and C must all be greater than 1\n";
        return 1;
    }

    //positive numbers show a forward path of where it came from
    //negative numbers show a reverse path of where it goes to
    int datum[10000] = {0}; 
    datum[1] = 1; //start point came from itself
    datum[C] = -C; //end point ends goes to itself
    std::deque<int> forward_todo;
    std::deque<int> backward_todo;
    std::deque<int> result;
    forward_todo.push_back(1);
    backward_todo.push_back(C);
    while(forward_todo.empty()==false && backward_todo.empty()==false) {
        if (calc_forward(datum, forward_todo, result))
            break;
        if (calc_backward(datum, backward_todo, result))
            break;
    }
    display_path(result);

    return 0;
}
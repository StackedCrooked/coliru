#include <algorithm>
#include <iterator>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

using HanoiPin = vector<unsigned>;

template<class PostAction>
void move_hanoi
(
    HanoiPin &from, HanoiPin &to, HanoiPin &temp,
    size_t count, PostAction post
)
{
    if(count>1)
    {
        move_hanoi(from, temp, to, count-1, post);
        move_hanoi(from, to, temp, 1, post);
        move_hanoi(temp, to, from, count-1, post);
    }
    else
    {
        to.push_back(from.back());
        from.pop_back();
        post();
    }
}

int main()
{
    auto count=5;
    HanoiPin a,b,c;
    generate_n(back_inserter(a), count, [=]() mutable
    {
        return count--;
    });
    auto print_hanoi=[](HanoiPin &h)
    {
        cout << "|";
        for(auto x : h)
            cout << x << "-";
        cout << endl;
    };
    auto printer=[&]
    {
        print_hanoi(a);
        print_hanoi(b);
        print_hanoi(c);
        cout << endl;
    };
    printer();
    move_hanoi(a,b,c,a.size(),printer);
}

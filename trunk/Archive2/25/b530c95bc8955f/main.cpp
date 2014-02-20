#include <algorithm>
#include <vector>
#include <functional>

typedef std::function<int(int)> fun_type;

struct composed{
    fun_type first;
    fun_type second;
    
    int operator()(int i)
    {
        return second(first(i));
    }
};

composed do_compose(fun_type first, fun_type second)
{
    composed c = { first, second };
    return c;
}

int noop(int i){ return i; }
int plus5(int i){ return i + 5; }
int times10(int i){ return i * 10; }
int minus20(int i){ return i - 20; }
int dividedBy2(int i){ return i / 2; }

#include <iostream>

int main(){
    std::vector<fun_type> funs = { plus5, times10, minus20, dividedBy2 };
    composed noop_ = { noop, noop }; // needed because 'std::accumulate' is stupid
    fun_type final = std::accumulate(funs.begin(), funs.end(), noop_, do_compose);
    
    // what the accumulate above does:
    composed plus5_times10 = { plus5, times10 };
    composed plus5_times10_minus20 = { plus5_times10, minus20 };
    composed final2 = { plus5_times10_minus20, dividedBy2 };
    
    std::cout << final(5) << " == " << final2(5) << " == " 
              // what it all comes down to:
              << dividedBy2(minus20(times10(plus5(5)))) << '\n';;
}
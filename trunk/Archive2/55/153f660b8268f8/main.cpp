#include <functional>
#include <vector>

int main()
{ 
    std::vector<int> data;
    
    /* EXACT EXAMPLE FROM SCOTT MAYERS BOOK TO SHOW THE TWO THINGS BELOW ARE EQUIVALENT */
    auto func = [data = std::move(data)] () mutable {data.clear();};
    auto mayers = std::bind([](std::vector<int>& data) mutable {data.clear();}, std::move(data));

    /* BUT mutable is not necessary for the bind object of THE ABOVE example */
    auto me = std::bind([](std::vector<int>& data) {data.clear();}, std::move(data));

    mayers();
    func();    
    me(); // ok, that is, mutable is NOT necessary as opposite to what Mayers says
}

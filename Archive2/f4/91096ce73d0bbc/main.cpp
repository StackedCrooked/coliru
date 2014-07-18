#include <locale>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
 
int main()
{
    std::vector<std::wstring> v = {L"жил", L"был", L"кот"};
    std::sort(v.begin(), v.end(), std::locale("ru_RU.UTF8"));
    assert(v[0] == L"был");
    assert(v[1] == L"жил");
    assert(v[2] == L"кот");
}
#include<functional>

template <typename T>
struct sList
{
    sList() = default;
    
    template<typename FunctionType>
    void DoForEachList(FunctionType pFunc) const
    {
        for(auto p = this; p; p = p->pNext)
            pFunc(p);
    }


    sList *pNext = nullptr;
};

int main()
{
    const sList<unsigned char> cvobj;
    cvobj.DoForEachList([] (auto pCurr) {/* Do something */});

    sList<unsigned char> obj;
    obj.DoForEachList([] (auto pCurr) {/* Do something */});
}
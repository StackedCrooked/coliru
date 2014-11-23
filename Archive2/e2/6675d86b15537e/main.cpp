#include <initializer_list>

template <typename T>
struct sList
{
    sList(std::initializer_list<T>);

private:
    static inline void DoForEachListHelper(auto this_, auto pFunc)
    {
        for(auto p = this_; p; p = p->pNext)
            pFunc(p);
    }

public:
    inline void DoForEachList(auto pFunc)
    {
        DoForEachListHelper(this, pFunc);
    }

    inline void DoForEachList(auto pFunc) const
    {
        DoForEachListHelper(this, pFunc);
    }

    ~sList();

    T dat;

    sList *pNext = nullptr;
};

extern const sList<unsigned char> cvobj;

int main()
{
    cvobj.DoForEachList([] (auto pCurr) { });
}
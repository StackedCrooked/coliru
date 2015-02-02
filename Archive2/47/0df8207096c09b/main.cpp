#include <iostream>
#include <thread>
#include <utility>

using namespace std;

template <typename T>
class OnExitImpl : private T
{
public:
    template <typename Y>
    OnExitImpl(Y&& todo) : T(std::forward<Y>(todo)), _doIt(true) {}

    OnExitImpl(OnExitImpl&& other) : T(std::move(static_cast<T&>(other))), _doIt(other._doIt)
    {
        other._doIt = false;
    }

    ~OnExitImpl()
    {
        if (_doIt)
        {
            (*this)();
        }
    }

    void Cancel()
    {
        _doIt = false;
    }

    OnExitImpl& operator=(OnExitImpl&& other)
    {
        this->T::operator=(std::move(static_cast<T&>(other)));
        _doIt = other._doIt;
        other._doIt = false;
    }

private:
    bool _doIt;
};

template <typename T>
OnExitImpl<T> OnExit(T action)
{
    return OnExitImpl<T>(std::move(action));
}

int FetchMultithreaded(int stmt)
{
    auto onExit = OnExit([&](){ cout << stmt << endl; });

    std::thread fetchThread([&]()
    {
        auto onExit = OnExit([&](){ cout << stmt << endl; });
    });

    return 0;
}

int main()
{
    return FetchMultithreaded(0);
}

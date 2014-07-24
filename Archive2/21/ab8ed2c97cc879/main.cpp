#include <utility>



template<typename F>
struct ScopeGuard
{
    ScopeGuard(F&& f) : mFunction(std::forward<F>(f)) { }

    // disable copy
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    // enable move
    ScopeGuard(ScopeGuard&&) noexcept = default;
    ScopeGuard& operator=(ScopeGuard&&) noexcept = default;

    ~ScopeGuard()
    {
        if (mActive)
        {
            mFunction();
        }
    }

    void release()
    {
        mActive.release();
    }

private:
    F mFunction;

    // Movable boolean.
    struct Flag
    {
        Flag() : mFlag(true) {}

        Flag(Flag&& rhs) noexcept :
            mFlag(rhs.mFlag)
        {
            rhs.mFlag = false;
        }

        Flag& operator=(Flag&& rhs) noexcept
        {
            mFlag = rhs.mFlag;
            rhs.mFlag = false;
            return *this;
        }

        Flag(const Flag&) = default;
        Flag& operator=(const Flag&) = default;

        explicit operator bool() const { return mFlag; }

        void release() { mFlag = false; }

    private:
        bool mFlag;
    };

    Flag mActive;
};


template<typename F>
inline ScopeGuard<F> make_scope_guard(F&& f)
{
    return ScopeGuard<F>(std::forward<F>(f));
}


#include <iostream>

int main()
{
    auto guard = make_scope_guard([]{ std::cout << "bye" << std::endl; });
}
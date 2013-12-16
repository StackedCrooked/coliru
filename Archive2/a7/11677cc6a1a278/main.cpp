

// support for GCC 4.5 and GCC 4.6 which return bool instead of future_status
enum class FutureStatus 
{
    Ready,
    Deferred,
    Timeout
};


template<typename Future, typename Rep, typename Period>
inline FutureStatus Wait(Future&& fut, std::chrono::duration<Rep, Period> duration)
{

    #if __GNUC_MINOR__ < 7
    if (!fut.wait_for(duration)) // GCC 4.5 and GCC 4.6 return bool
    {
        return FutureStatus::Timeout;
    }
    #else
    // NOTE: If the future was launched  with the deferred launch policy then
    //       future_status::deferred should be returned. However, libstdc++
    //       returns std::future_status::timeout (BUG). This code tries to
    //       to work around this.
    auto start_time = Clock::now();
    if (fut.wait_for(duration) == std::future_status::timeout)
    {
        auto elapsed = Clock::now() - start_time;
        if (elapsed < duration)
        {
            // libstdc++ wrongly returned timeout before expiration
            return FutureStatus::Deferred;
        }
        else
        {
            return FutureStatus::Timeout;
        }
    }
    #endif
    return FutureStatus::Ready;
}


template<typename Future, typename Rep, typename Period>
inline auto Get(Future&& fut, std::chrono::duration<Rep, Period> duration) -> decltype(fut.get())
{
    if (Wait(fut, duration) == FutureStatus::Timeout)
    {
        throw std::runtime_error("Timeout while waiting for future result.");
    }
    return fut.get();
}


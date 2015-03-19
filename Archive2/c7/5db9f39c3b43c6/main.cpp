


struct Processor
{
    // ptmf fuckery
    // called from derived class (so no "this" pointer is passed here)
    template<typename R, typename Derived, typename ...Params, typename ...Args>
    R post_task(R(Derived::*method)(Params...), Args&& ...args)
    {
        static_assert(std::is_base_of<Processor, Derived>::value, "");
        std::packaged_task<R()> task(std::bind(method, &dynamic_cast<Derived&>(*this), std::forward<Args>(args)...));
        auto fut = task.get_future();
        task_queue.push(std::move(task));
        return fut.get();
    }
};


struct LatencyCounter : PacketProcessor
{
    Foo process(Bar bar, Har har)
    {
        return post_task(&LatencyCounter::process_async, foo, bar);
    }
    
private:
    Foo process_async(Bar, Har);
    
};



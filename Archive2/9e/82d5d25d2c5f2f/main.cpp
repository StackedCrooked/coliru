

// pops tasks from a tbb::concurrent_priority_queue<FutureTask>
void scheduler_thread()
{
    try
    {
        for (;;)
        {
            FutureTask f;
            if (!tasks_queue.try_pop(f))
            {
                goto yield;
            }

            if (f.timeout() < Clock::now())
            {
                // too early, push it back
                tasks_queue.push(f);
                goto yield;
            }

            // invoke the functor
            f(Internal());
            
            // don't yield as long as we are successful
            continue;
            
        yield:
            sched_yield();
        }
    }
    catch (const Detail::QuitMessage&)
    {
        LOG(Info) << "Scheduler: received QuitMessage. Thread will now exit.";
    }
    catch (const std::exception& exc)
    {
        LOG(Error) << "Scheduler: caught exception: " << exc.what();
        throw;
    }
    catch (...)
    {
        LOG(Error) << "Scheduler: caught anonymous exception.";
        throw;
    }
}

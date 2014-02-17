

// pops tasks from a tbb::concurrent_priority_queue<FutureTask>
void scheduler_thread()
{
    try
    {
        goto entry_point;

        for (;;)
        {
            sched_yield();

        entry_point:
            FutureTask f;
            if (!tasks_queue.try_pop(f))
            {
                // queue is empty
                continue;
            }

            if (f.timeout() < Clock::now())
            {
                // too early, push it back
                tasks_queue.push(f);
                continue;
            }

            // run the task
            f(Internal());
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

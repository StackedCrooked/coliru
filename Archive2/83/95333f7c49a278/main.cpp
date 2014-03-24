

    static int64_t get_current_us()
    {
        timeval tv;
        gettimeofday(tv, NULL);
        return tv.tv_sec * 1000000L + tv.tv_usec;
    }

    inline int64_t get_elapsed_us() const
    {
        return get_current_us() - start_time;
    }

    struct StartTime
    {
        StartTime() : time_us() {}

        operator int64_t() const
        {
            // lazy instantiation to elimate delay between session creation
            // and first send
            if (!time_us)
            {
                time_us = get_current_us();
            }
            return time_us;
        }

    private:
        mutable int64_t time_us;
    };

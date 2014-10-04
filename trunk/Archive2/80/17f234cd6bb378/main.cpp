

// From boost/lockfree/spsc_queue.hpp

void reset(void)
{
    if ( !boost::has_trivial_destructor<T>::value ) {
        // make sure to call all destructors!

        T dummy_element;
        while (pop(dummy_element))
        {}
    } else {
        write_index_.store(0, memory_order_relaxed);
        read_index_.store(0, memory_order_release);
    }
}

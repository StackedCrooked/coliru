template<class T, class ...Us>
T* allocateEffect(Us...Vs) { 
    std::unique_ptr<char[], decltype(free_some_memory)> raw(allocate_some_memory(sizeof(T)),free_some_memory);
    T* ret = new (raw.get()) T(std::forward<Us>(vs)...);
    raw.release();
    return ret;
}
    
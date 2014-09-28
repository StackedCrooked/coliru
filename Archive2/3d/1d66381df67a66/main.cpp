
template<typename T, typename VecIterator, typename Iterator> void better_insert(std::vector<T>& vec, VecIterator where, Iterator begin, Iterator end) {
    auto rollback_point = vec.end();
    // First we re-use the space available in the current buffer.
    try {
        while(begin != end && vec.size() != vec.capacity()) {
            vec.push_back(*begin);
            ++begin;
        }
    } catch(...) {
        vec.erase(rollback_point, vec.end());
        throw;
    }
    // It did not run out. Just move the elements to the correct place and we're done.
    if (begin == end) {
        std::rotate(where, rollback_point, vec.end());
        return;
    }
    // It did run out. We need a new buffer (or possibly several depending on how large things got).
    T* last_constructed = nullptr;
    template<typename T> struct no_initialize : std::allocator<T> {
        no_initialize(std::unordered_set<T*>& arg) : constructed(arg) {}
        std::unordered_set<T*>& constructed;
        void construct(T* p) {}
        template<typename... Args> void construct(T* p, Args&&... args) {
            new (p) T(std::forward<Args>(args)...);
            constructed.insert(p);
        }
        void destroy(T* p) {
            if (constructed.find(p) != constructed.end()) {
                p->~T();
                constructed.erase(p);
            }
        }
    };
    std::unordered_set<T*> constructed;
    // The insertion point is going to be "where" adjusted for the new buffer + however many we inserted so far.
    std::vector<T, no_initialize<T>> new_buffer(no_initialize<T>(constructed));
    new_buffer.reserve(vec.size() * 1.5);
    auto start_size = (where - vec.size()) + (vec.end() - rollback_point);
    new_buffer.resize(start_size);
    try {
        while(begin != end) {
            new_buffer.push_back(*begin);
            ++begin;
        }
    } catch(...) {
        vec.erase(rollback_point, vec.end());
        throw;
    }
    auto added_elements = new_buffer.size() - start_size;
    // First, make sure we have enough space for the insertion.
    new_buffer.resize(vec.size() + added_elements);
    
    // move_if_noexcept the elements from the previous buffer over in the order in which they need to appear in the new buffer.
    // Add them to the constructed set so that we properly destruct them.
    auto dest = new_buffer.begin();
    try {
        // First, the elements that aren't disturbed by the insertion.
        for(auto it = vec.begin(); it != where; ++it) {
            new (&*dest) T(std::move_if_noexcept(*it));
            constructed.insert(dest);
            ++dest;
        }
        // Second, the elements we placed in the slack space at the end of the existing buffer.
        for(auto it = rollback_point; it != vec.end(); ++it) {
            new (&*dest) T(std::move_if_noexcept(*it));
            constructed.insert(dest);
            ++dest;
        }
        // Third, the elements we need to move to make space for the ones we just created.
        for(auto it = where; it != rollback_point; ++it) {
            new (&*dest) T(std::move_if_noexcept(*it));
            constructed.insert(dest);
            ++dest;
        }
    } catch(...) {
        // Clean up the input vector.
        vec.erase(rollback_point, vec.end());
        throw;
    }
    // Now just swap the old buffer for the new one.
    vec.swap(new_buffer);
}
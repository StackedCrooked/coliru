class R
{
    mutable std::shared_mutex m;
    /* data */
public:
    R& operator=(const R& other)
    {
        // requires exclusive ownership to write to *this
        std::unique_lock<std::shared_mutex> lhs(mut, std::defer_lock);
        // requires shared ownership to read from other
        std::shared_lock<std::shared_mutex> rhs(other.mut, std::defer_lock);
        lock(lhs, rhs);
        /* assign data */
        return *this;
    }
}
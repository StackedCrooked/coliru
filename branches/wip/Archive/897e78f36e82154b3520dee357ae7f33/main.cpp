struct X
{
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {assign_impl(first, last, std::iterator_traits<InputIterator>::iterator_category());}
private:
    template <typename InputIterator>
    void assign_impl(InputIterator first, InputIterator last, std::random_access_iterator_tag)
    {
        // Implementation for random access iterator...
    }
    template <typename InputIterator>
    void assign_impl(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
        // Implementation for non-random access iterator...
    }
};
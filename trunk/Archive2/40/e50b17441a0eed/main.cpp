#include <vector>
#include <iostream>

class circular_buffer
{
public:
    class iterator
    {
    public:
        iterator(const circular_buffer& buffer, unsigned position)
            : m_buffer(buffer)
            , m_position(position)
        {
        }

        iterator& operator++()
        {
            ++m_position;
            if (m_position == m_buffer.capacity()) {
                m_position = 0;
            }
            return *this;
        }

        int operator*()
        {
            return m_buffer.at(m_position);
        }

        bool operator==(const iterator& other)
        {
            return m_position == other.m_position;
        }

        bool operator!=(const iterator& other)
        {
            return !(*this == other);
        }

    private:
        const circular_buffer& m_buffer;
        unsigned m_position;
    };

public:
    circular_buffer()
        : m_buffer()
        , m_front_id(0)
        , m_back_id(0)
        , m_size(0)
    {
    }

    unsigned front_id() const
    {
        return m_front_id;
    }

    unsigned back_id() const
    {
        return m_back_id;
    }

    bool is_empty() const
    {
        return size() == 0;
    }

    bool is_full() const
    {
        return size() == m_buffer.size();
    }

    unsigned size() const
    {
        return m_size;
    }

    unsigned capacity() const
    {
        return m_buffer.size();
    }

    int at(unsigned id) const
    {
        return m_buffer[id];
    }

    void push_back(int n)
    {
        m_buffer[m_back_id] = n;
        increment_back();
        if (m_front_id == m_back_id) {
            increment_front();
        } else {
            ++m_size;
        }
    }

    void pop_front()
    {
        increment_front();
        --m_size;
    }

    void clear()
    {
        m_front_id = m_back_id = m_size = 0;
    }

    void reserve(unsigned capacity)
    {
        m_buffer.resize(capacity, 0);
    }

    iterator begin() const
    {
        return iterator(*this, m_front_id);
    }

    iterator end() const
    {
        return iterator(*this, m_back_id);
    }

public:
    void increment_front()
    {
        ++m_front_id;
        if (m_front_id == capacity()) {
            m_front_id = 0;
        }
    }

    void increment_back()
    {
        ++m_back_id;
        if (m_back_id == capacity()) {
            m_back_id = 0;
        }
    }

    void print()
    {
        std::cout << "Contents: ";
        auto first = begin();
        for (; first != end(); ++first) {
            std::cout << *first << " ";
        }
        std::cout << *first << " " << std::endl;
    }

private:
    std::vector<int> m_buffer;
    unsigned m_front_id;
    unsigned m_back_id;
    unsigned m_size;
}; // class circular_buffer

int main()
{
    circular_buffer cb;
    cb.reserve(3);

    // Insert three elements into the buffer.
    cb.push_back(1);
    cb.push_back(2);
    cb.push_back(3);

    cb.print(); // == 1, 2, 3

    // The buffer is full now, so pushing subsequent
    // elements will overwrite the front-most elements.

    cb.push_back(4);  // Overwrite 1 with 4.
    cb.push_back(5);  // Overwrite 2 with 5.

    // The buffer now contains 3, 4 and 5.
    cb.print();

    // Elements can be popped from either the front or the back.
    cb.pop_front(); // 3 is removed.

    // Leaving only one element with value = 4.
    cb.print();
}

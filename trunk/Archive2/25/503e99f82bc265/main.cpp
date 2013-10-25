SeqNum
{
    // Note: there is no default constructor because that could lead to bugs.
    explicit SeqNum(uint32_t inValue) : mValue(inValue) {}

    uint32_t get() const { return mValue; }

    SeqNum& operator++()
    {
        ++mValue;
        return *this;
    }

    SeqNum& operator+=(uint32_t n)
    {
        mValue += n;
        return *this;
    }

    friend bool operator==(SeqNum lhs, SeqNum rhs)
    {
        return lhs.mValue == rhs.mValue;
    }

    friend bool operator!=(SeqNum lhs, SeqNum rhs)
    {
        return lhs.mValue != rhs.mValue;
    }

    friend bool operator<(SeqNum lhs, SeqNum rhs)
    {
        return static_cast<int32_t>(lhs.mValue - rhs.mValue) < 0;
    }

    friend bool operator<=(SeqNum lhs, SeqNum rhs)
    {
        return static_cast<int32_t>(lhs.mValue - rhs.mValue) <= 0;
    }

    friend bool operator>(SeqNum lhs, SeqNum rhs)
    {
        return static_cast<int32_t>(lhs.mValue - rhs.mValue) > 0;
    }

    friend bool operator>=(SeqNum lhs, SeqNum rhs)
    {
        return static_cast<int32_t>(lhs.mValue - rhs.mValue) >= 0;
    }

    friend SeqNum operator+(SeqNum lhs, uint32_t n)
    {
        return SeqNum(lhs.get() + n);
    }

    friend SeqNum operator-(SeqNum lhs, uint32_t n)
    {
        return SeqNum(lhs.get() - n);
    }

    friend uint32_t operator-(SeqNum lhs, SeqNum rhs)
    {
        assert(lhs >= rhs);
        return lhs.get() - rhs.get();
    }

    friend std::ostream& operator<<(std::ostream& os, SeqNum seq)
    {
        return os << seq.get();
    }

    uint32_t mValue;
};

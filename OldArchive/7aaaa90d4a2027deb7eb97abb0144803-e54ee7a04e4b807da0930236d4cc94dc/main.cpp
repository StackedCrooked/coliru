

inline uint16_t OnesComplementSum(uint16_t a, uint16_t b)
{
    static const uint32_t cMaxValue = uint32_t(-1);
    static const unsigned cNumBits = 8 * sizeof(uint16_t);

    uint32_t sum = a + b;
    while (sum > cMaxValue)
    {
        sum = (sum >> cNumBits) + (sum & cMaxValue);
    }
    return static_cast<uint16_t>(sum);
}


inline uint16_t OnesComplementSum(uint16_t n1,
                                  uint16_t n2,
                                  uint16_t n3,
                                  uint16_t n4)
{
    return OnesComplementSum(OnesComplementSum(n1, n2),
                             OnesComplementSum(n3, n4));
}


inline uint16_t OnesComplementSum(uint16_t n1,
                                  uint16_t n2,
                                  uint16_t n3,
                                  uint16_t n4,
                                  uint16_t n5,
                                  uint16_t n6,
                                  uint16_t n7,
                                  uint16_t n8)
{
    return OnesComplementSum(OnesComplementSum(n1, n2, n3, n4),
                             OnesComplementSum(n5, n6, n7, n8));
}


inline uint16_t OnesComplementSum(const uint8_t* begin, int length)
{
    if (length >= 16)
    {
        uint16_t halves[8];
        memcpy(halves, begin, sizeof(halves));
        return OnesComplementSum
        (
            OnesComplementSum(halves[0], halves[1], halves[2], halves[3], halves[4], halves[5], halves[6], halves[7]),
            OnesComplementSum(begin + 16, length - 16)
        );
    }
    else if (length >= 8)
    {
        uint16_t halves[4];
        memcpy(halves, begin, sizeof(halves));
        return OnesComplementSum
        (
            OnesComplementSum(halves[0], halves[1], halves[2], halves[3]),
            OnesComplementSum(begin + 8, length - 8)
        );
    }
    else if (length >= 4)
    {
        uint16_t halves[2];
        memcpy(halves, begin, sizeof(halves));
        return OnesComplementSum
        (
            OnesComplementSum(halves[0], halves[1]),
            OnesComplementSum(begin + 4, length - 4)
        );
    }
    else if (length == 3)
    {
        uint16_t halves[2];
        halves[1] = 0;
        memcpy(halves, begin, length);
        return OnesComplementSum(halves[0], halves[1]);
    }
    else if (length == 2)
    {
        return *reinterpret_cast<const uint16_t*>(begin);
    }
    else if (length == 1)
    {
        return static_cast<uint16_t>(begin[0]);
    }
    else
    {
        return 0;
    }
}
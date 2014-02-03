#include <cstdint>
#include <cstdlib>

// typedef uint8_t id_t;
enum class MessageID { WorldPeace };

class Message
{
    uint8_t* m_data;         // current memory
    uint8_t m_localData[64]; // upto 64 bytes.
    id_t m_messageId;
    std::size_t m_size; // amount of data used
    std::size_t m_capacity; // amount of space available
    // ...

public:
    Message(std::size_t requestSize, id_t messageId)
        : m_data(m_localData)
        , m_messageId(messageId)
        , m_size(0), m_capacity(sizeof(m_localData))
    {
        grow(requestSize);
    }

    void grow(std::size_t newSize)
    {
        if (newSize > m_capacity)
        {
            m_data = realloc((m_data == m_localData) ? nullptr : m_data, newSize);
            assert(m_data != nullptr); // my system uses less brutal mem mgmt
            m_size = newSize;
        }
    }

    template<typename T>
    T* allocatePtr()
    {
        size_t offset = size;
        grow(offset + sizeof(T));
        return (T*)(m_data + offset);
    }

    template<typename T, typename... Args>
    Message(id_t messageId, Args...&& args)
        : Message(sizeof(T), messageID)
    {
        // we know m_data points to a large enough buffer
        new ((T*)m_data) T (std::forward<Args>(args)...);
    }
};

    template<typename T>
    Message(id_t messageId, T&& src)
        : Message(sizeof(T), messageID)
    {
        // we know m_data points to a large enough buffer
        new ((T*)m_data) T (src);
    }
    
    int main()
    {
        Message outgoing(MessageID::WorldPeace, MyStruct(wpArg1, wpArg2, wpArg3));
    }
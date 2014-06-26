// for http://stackoverflow.com/a/24438482/89999
#include <iostream>


//Native message (not in network endian format)
struct Message
{
    short val;
    explicit Message(short v): val(v){}
};

//Network endian format of Message
struct OtaMessage
{
    short val;

    operator Message() const
    {
        return Message(val >> 8 | val << 8); 
    }

    explicit OtaMessage(const Message& m)
        : val(m.val >> 8 | m.val << 8)
    {}
};

template <typename T>
struct OtaConverter {
    // using ota_type = T; -- don't provide a base ota_type
};
    
template <> struct OtaConverter<Message> {
     using ota_type = OtaMessage;
};

class BufferInserter
{
public:
    BufferInserter(char* buffer)
        :buf(buffer)
    {}

    template<typename T>
    char* insertStruct(T s, typename OtaConverter<T>::ota_type* = 0)
    {
        using OT = typename OtaConverter<T>::ota_type;
        const std::size_t size = sizeof(OT);
        *reinterpret_cast<OT*>(buf) = OT(s);
        buf += size;
        return buf;
    }
    
private:
    char* buf;
};

int main()
{
    Message m(0x0102);
    
    char buf[256];
    BufferInserter ins(buf);
    ins.insertStruct(m);
    
    std::cout << (m.val & 0xff) << (m.val >> 8) << "\n";
    std::cout << (int)buf[0] << (int)buf[1] << "\n";
}
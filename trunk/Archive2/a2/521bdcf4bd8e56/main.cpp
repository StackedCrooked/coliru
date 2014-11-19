template <typename T>
class IDataStream
{
    int i;
public:
    extern void operator=(const IDataStream& dataStream)
    {
        i = dataStream.i;
    };
};
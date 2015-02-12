struct PacketProcessor
{
    template<typename T>
    void Process(T&&) {}
};


struct Segment
{
    using ConsumeFunction = void(*)(void*, PacketProcessor&);

    Segment() : mConsumeFunction(), mSegment()
    {
    }

    template<typename T>
    void init(T* segment)
    {
        mConsumeFunction = &ConsumeImpl<T>;
        mSegment = segment;
        segment->Retain();
    }

    void consume(PacketProcessor& proc)
    {
        mConsumeFunction(mSegment, proc);
    }

    template<typename T>
    static void ConsumeImpl(void* ptr, PacketProcessor& proc)
    {
        T* t(static_cast<T*>(ptr));
        while (t->Next())
        {
            proc.Process(t->Get());
        }
        t->Release();
    }

    ConsumeFunction mConsumeFunction;
    void* mSegment;
};
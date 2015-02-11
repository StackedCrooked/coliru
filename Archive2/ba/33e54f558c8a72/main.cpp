




struct PacketProcessor
{
    struct PacketGroup
    {
        using Pool = boost::lockfree::stack<PacketGroup*>;
        
        static Pool& GetPool()
        {
            static Pool fPool;
            return fPool;
        }
        
        static PacketGroup* Acquire(const std::shared_ptr<void>& inSegmentOwner)
        {
            PacketGroup* group;
            if (!GetPool().pop(group))
            {
                group = new PacketGroup;
            }
            
            group->mSegmentOwner = inSegmentOwner;
            return group;
        }
    
        static void Release(PacketGroup* group)
        {
            group->mSegmentOwner.reset();
            GetPool().push(group);
        }
        
        void flush()
        {
            for (PacketProcessor* processor : mPacketProcessors)
            {
                processor->Process(*this);
            }
        }
        
        std::vector<Packet*> mPackets;
        std::vector<PacketProcessor*> mPacketProcessors;
        std::shared_ptr<void> mSegmentOwner;
    };
    
    PacketGroup* getGroup(const std::shared_ptr<void>& inSegmentOwner)
    {
        if (!mCurrentGroup)
        {
            mCurrentGroup = Acquire(inSegmentOwner);
        }
        return mCurrentGroup;
    }
    
    
    void ProcessGroup(const PacketGroup& inPacketGroup)
    {
    }
    
    PacketGroup* mCurrentGroup;
};



void process_segment()
{
    std::shared_ptr<Consumer> consumer = get_consumer();
    while (Packet* packet : consumer)
    {
        PacketGroup* group = GetProcessor(packet).getGroup(consumer);
        group->mPackets.push_back(packet);
    }
}


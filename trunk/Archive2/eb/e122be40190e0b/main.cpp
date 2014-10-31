



template<typename CLS, typename LLS, typename ...>
struct Session
{
    using Header = typename CLS::Header;
    
    void push(Header& header)
    {
        getCLS().do_push(header);
    }
    
    void push(Packet& packet)
    {
        prepend_header(packet);
        static_cast<LLS&>(*this).push(packet);
        
    }
};



struct CompositeSession
{
    template<typename Tag>
    void push(Session& session, Header& header)
    {
        session.update(header);
    }
    
    // pop
    void pop(const TCPHeader& tcp, const IPv6Header& ip6, const EthernetHeader& eth)
    {
        if (!validate(ip6))
        {
            return;
        }
        
        if (!hasIP(ip6.dst_ip))
        {
            return;
        }
        
         if (!validate(tcp))
        {
            return;
        }
        
        if (tcp.dst_port != Get<LocalPort>(*this))
        {
            
        }
        
        
        
    }
    
    Sessions<TCP, IPv4, Ethernet> mSessions;
    CompositeHeader<TCP, IPv4, Ethernet> mHeader;
};



struct TCPSession
{
    void do_push(TCPHeader& tcpheader, ByteRange payload)
    {
        tcpheader.seqnum += payload.size();
        tcpheader.checksum = 0;
        tcpheader.checksum = Checksum16(tcpheader, mPseudoHeader, payload);
        
        tcpheader.acknum += mReceivedUnacked;
        mReceivedUnacked = 0;
    }
    
    template<typename IPHeader, typename ...Tail>
    void do_pop(TCP& state, const TCPHeader& receive_header, const IPHeader& ipheader, const Tail& ...)
    {   
        if (Checksum16(tcpheader, ipheader, GetPayload(tcpheader)) != 0)
        {
            // invalid checksum
            return;
        }
        
        if (receive_header.ack == mUnacked
        
        // mReceivedSeqnum = tcpheader.seqnum;
    }    
    
    uint32_t mSendUnacked;
    uint32_t mSendNext;
    uint32_t mSendWindow;
    uint32_t mReceiveUnacked;
    std::vector<Packet> mUnacked;
};



struct IPv6Session
{
    template<typename ...Headers>
    void do_push(Headers&&...)
    {
        // Once an IPv6 session is established its header doesn't change.
    }
};



struct EthernetSession
{
    template<typename ...Headers>
    void do_push(Headers&&...)
    {
        // ethernet header never changes
    }
};



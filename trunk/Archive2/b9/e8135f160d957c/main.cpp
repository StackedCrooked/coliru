



void flip(EthernetHeader& header)
{
    std::swap(header.source, header.mSourceMAC);
}

void flip(IPv4Header& header)
{
    std::swap(header.source_ip, header.destination_ip);
}

void flip(IPv6Header& header)
{
    std::swap(header.source_ip, header.destination_ip);
}

void pop(Stack& stack, EthernetDecoder);

// layer 3
void pop(Stack& stack, IPv4Decoder, EthernetDecoder);
void pop(Stack& stack, IPv6Decoder, EthernetDecoder);

// layer 4 on ip
void pop(Stack& stack, ICMPDecoder, IPv4Decoder, EthernetDecoder);
void pop(Stack& stack, UDPDecoder, IPv4Decoder, EthernetDecoder);
void pop(Stack& stack, TCPDecoder, IPv4Decoder, EthernetDecoder);

// layer 5 on ip
void pop(Stack& stack, HTTPDecoder, TCPDecoder, IPv4Decoder, EthernetDecoder eth);
void pop(Stack& stack, DHCPDecoder, UDPDecoder, IPv4Decoder, EthernetDecoder eth);


void pop(Stack& stack, EthernetDecoder ethdec)
{
    switch (ethdec.getEtherType())
    {
        case EtherType::ARP:
        {
            pop(stack, ARPDecoder(ethdec), ethdec);
            break;
        }
        case EtherType::IPv4:
        {
            pop(stack, IPv4Decoder(ethdec), ethdec);
            break;
        }
        case EtherType::IPv6:
        {
            pop(stack, IPv6Decoder(ethdec), ethdec);
            break;
        }
    }
}

void pop(Stack& stack, IPv4Decoder ipdec, VLANDecoder* vlandec, EthernetDecoder ethdec)
{
    switch (ipdec.getIPProtNum())
    {
        case IPProtNum::TCP:
        {
            pop(stack, TCPDecoder(ipdec), ipdec, vlandec, ethdec);
            break;
        }
        case IPProtNum::UDP:
        {
            pop(stack, TCPDecoder(ipdec), ipdec, vlandec, ethdec);
            break;
        }
    }
}

template<typename L3Dec>
void pop(Stack& stack, TCPDecoder tcpdec, L3Dec ipdec, VLANDecoder* vlandec, EthernetDecoder ethdec)
{
    auto port = tcpdec.getDestinationPort();
    L5Protocol* l5 = stack.getL5Protocol(port);
    if (!l5)
    {
        LOG(Trace) << "There is no l5 protocol on port " << port;
        return;
    }
    
    l5->pop(tcpdec, ipdec, vlandec, ethdec);
}


template<typename L3>
struct HTTP : L5Protocol
{
    typedef typename L3::Decoder L3Dec;
 
    template<typename ...LowerLayerProtocols>
    void pop(Stack& stack, HTTPDecoder httpdec, LowerLayerProtocols&&... protocols)
    {
        Packet packet;
        
        // push the http payload
        packet.push_front(get_reponse(httpdec));
        
        
        unpack(push(stack, std::forward<LowerLayerProtocols>(protocols))...);
        // ^ exands to
        //      unpack(push(stack, packet, tcpdec),
        //             push(stack, packet, ipdec),
        //             push(stack, packet, ethdec));
        
        
        // copy all input headers
        packet.push_front(eth.begin(), httpdec.begin());
        
        // swap source and destination fields
        auto& l2_header = *reinterpret_cast<EthernetHeader*>(packet.data());
        flip(l2_header);
        
        auto& l3_header = *reinterpret_cast<L3Header*>(vlandec ? vlandec->payload() : ethdec.payload());
        flip(l3_header);
        
        auto& l4_header = *reinterpret_cast<TCPHeader*>(l3dec.payload());
        flip(l4_header);
        
        // write to socket
        stack.write(packet);
    }
}






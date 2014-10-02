struct EthernetDecoder {};
struct VLANDecoder {};
struct IPv4Decoder {};
struct IPv6Decoder {};
struct TCPDecoder {};
struct UDPDecoder {};

void pop(EthernetDecoder ethdec);

template<typename ...Tail> void pop(Stack<VLAN>&, VLANDecoder vlandec, Tail... tail);
template<typename ...Tail> void pop(Stack<IPv4>&, IPv4Decoder ipdec, Tail... dec);
template<typename ...Tail> void pop(Stack<IPv6>&, IPv6Decoder ipdec, Tail... dec);

template<typename ...Tail> void pop(TCPDecoder ipdec, Tail... dec);
template<typename ...Tail> void pop(UDPDecoder ipdec, Tail... dec);


void pop(StackT& stackt, Stack<Ethernet>& stack, EthernetDecoder ethdec)
{
    switch (ethdec.getEtherType())
    {
        case VLAN:
        {
            VLANDecoder vlandec(ethdec);
            pop(stack, stack, vlandec, ethdec);
            break;
        }
        case IPv4:
        {
            IPv4Decoder ipdec(ethdec);
            pop(ipdec, ethdec);
            break;
        }
        case IPv6:
        {
            IPv6Decoder ipdec(ethdec);
            pop(ipdec, ethdec);
            break;
        }
    }
}


void pop(VLANDecoder vlandec, Tail... tail)
{
    switch (vlandec.getEtherType())
    {
        case VLAN:
        {
            break; // only one vlan tag allowed
        }
        case IPv4:
        {
            IPv4Decoder ipdec(ethdec);
            pop(ipdec, ethdec, tail...);
            break;
        }
        case IPv6:
        {
            IPv6Decoder ipdec(ethdec);
            pop(ipdec, ethdec, tail...);
            break;
        }
    }
}


void pop(IPv4Decoder ipdec, Tail... dec)
{
    switch (ipdec.getProtocol())
    {
        case TCP:
        {
            TCPDecoder tcpdec(ipdec);
            pop(tcpdec, ipdec, tail...);
            break;
        }
        case UDP:
        {
            UDPDecoder udpdec(ipdec);
            pop(udpdec, ipdec, tail...);
            break;
        }
    }
}


void pop(IPv6Decoder ipdec, Tail... dec)
{
    switch (ipdec.getProtocol())
    {
        case TCP:
        {
            TCPDecoder tcpdec(ipdec);
            pop(tcpdec, ipdec, tail...);
            break;
        }
        case UDP:
        {
            UDPDecoder udpdec(ipdec);
            pop(udpdec, ipdec, tail...);
            break;
        }
    }
}

template<typename ...Tail>
void pop(TCPDecoder ipdec, Tail... dec)
{
}


template<typename ...Tail>
void pop(UDPDecoder udpdec, Tail... tail)
{
    stack.pop(udpdec, tail...);
}







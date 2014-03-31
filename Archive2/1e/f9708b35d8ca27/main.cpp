
TEST_F(UDPTest, Packetv4)
{
    Packet packet;    
    packet.push_front("0123456789012345678901234567890123456789");

    auto src_mac  = MACAddress{ 0x00, 0xff, 0x23, 0x00, 0x00, 0x01 };
    auto src_ip   = IPv4Address{ 1, 1, 1, 1 };
    auto src_port = uint16_t(24810);

    auto dst_mac  = MACAddress{ 0x00, 0xff, 0x23, 0x00, 0x00, 0x01 };
    auto dst_ip   = IPv4Address{ 1, 1, 1, 2 };
    auto dst_port = uint16_t(24811);

    // Generate packet
    MakeUDPPacket(packet, src_port, dst_port, src_ip, dst_ip);
    MakeIPv4Packet(packet, IPProtNum::UDP, src_ip, dst_ip);
    MakeEthernetPacket(packet, src_mac, dst_mac, EtherType::IPv4);

    // Write out pcap (useful for checking with Wireshark)
    WritePCAP("UDPv4.pcap", packet);
}

struct msg_struct {
    int  msg_type;
    char msg_name[100];

    union X {
        struct {
            int     ID;
            char    ReportedTime[100];
            char    ReceivedAt[200];
            int     Number;
        } mess1;

        struct XB {
            char    host_ip[20];
            char    mac_addr[30];
            char    time_stamp[100];
        } mess2;
    } struct_type;
};

#include <boost/serialization/is_bitwise_serializable.hpp>
BOOST_IS_BITWISE_SERIALIZABLE(msg_struct)

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <sstream>
#include <iostream>
#include <cstring>
#include <iomanip>

int main()
{
    std::stringstream ss;
    boost::archive::binary_oarchive oa(ss);

    msg_struct msg;

    strncpy(msg.msg_name,                       "msg_name",     sizeof(msg.msg_name));
    strncpy(msg.struct_type.mess1.ReportedTime, "ReportedTime", sizeof(msg.struct_type.mess1.ReportedTime));
    strncpy(msg.struct_type.mess1.ReceivedAt,   "ReceivedAt",   sizeof(msg.struct_type.mess1.ReceivedAt));
    strncpy(msg.struct_type.mess2.host_ip,      "host_ip",      sizeof(msg.struct_type.mess2.host_ip));
    strncpy(msg.struct_type.mess2.mac_addr,     "mac_addr",     sizeof(msg.struct_type.mess2.mac_addr));
    strncpy(msg.struct_type.mess2.time_stamp,   "time_stamp",   sizeof(msg.struct_type.mess2.time_stamp));

    oa << boost::serialization::make_array(&msg, 1);

    for(auto c : ss.str())
        std::cout << std::hex << std::setfill('0') << std::setw(2) << ((int) c);

    boost::archive::binary_iarchive ia(ss);
    oa << boost::serialization::make_array(&msg, 1);
}

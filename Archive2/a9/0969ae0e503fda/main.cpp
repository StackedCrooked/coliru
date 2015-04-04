#include "snapshot.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <cstdint>


struct Packet
{
    Packet() : size(100), time(100), repeats(1000) {}
    Size size; Time time; Counter repeats;
};


std::vector<Packet> packets(20);
std::vector<Snapshot> snapshots(20);


int main()
{

using namespace std::chrono;
    auto start_time = steady_clock::now();

    for (Packet& packet : packets)
    {
        for (Snapshot& snapshot : snapshots)
        {
            snapshot.update(packet.repeats, packet.size, packet.size);
        }
    }

    auto elapsed = duration_cast<microseconds>(steady_clock::now() - start_time);

#ifdef REF
    std::cout << "By ref: " << elapsed.count() << " microseconds" << std::endl;
#else
    std::cout << "By val: " << elapsed.count() << " microseconds" << std::endl;
#endif
}

#include <iostream>
#include <random>
#include <cmath>
#include <iomanip>

int main()
{
    const double avg_packets_per_second = 4.1 ;
    const int min_packet_sz = 50 ;
    const int max_packet_sz = 760 ;
    const double variance = 300 ;

    std::exponential_distribution<double> inter_arrival_time( avg_packets_per_second ) ;
    std::normal_distribution<double> pkt_size( (min_packet_sz+max_packet_sz)/2.0, variance ) ;

    std::mt19937 rng( std::random_device{}() ) ;

    double time = 0 ;
    // generate 25 packets
    std::cout << std::fixed << std::setprecision(2) ;
    for( int i = 0 ; i < 25 ; ++i )
    {
        time += inter_arrival_time(rng) ;

        int sz ;
        do sz = std::round( pkt_size(rng) ) ;
        while( sz < min_packet_sz || sz > max_packet_sz ) ;

        std::cout << "at " << time << " seconds, packet with size "  << std::setw(3) << sz << " bytes\n" ;
    }
}

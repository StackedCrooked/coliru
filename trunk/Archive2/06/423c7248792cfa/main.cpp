#include <iostream>
#include <string>
#include <vector>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/indexed_by.hpp>
#include <boost/multi_index/ordered_index.hpp>



struct Track
{
    std::string album;
    std::string name;

    friend bool operator<(const Track& lhs, const Track& rhs)
    {
        if (lhs.album != rhs.album)
        {
            return lhs.album < rhs.album;
        }
        else
        {
            return lhs.name < rhs.name;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Track& track)
    {
        return os << "name=" << track.name << " album=" << track.album;
    }
};


using namespace boost::multi_index;

typedef multi_index_container<
    Track,
    indexed_by<
        ordered_unique<identity<Track>>,
        ordered_non_unique<member<Track, std::string, &Track::name>>,
        ordered_non_unique<member<Track, std::string, &Track::album>>
    >
> Tracks;


void print_by_id(const Tracks& tracks)
{
    std::cout << __FUNCTION__ << std::endl;
    for (const auto& track : tracks.get<0>())
    {
        std::cout << track << std::endl;
    }
    std::cout << std::endl;
}


void print_by_name(const Tracks& tracks)
{
    std::cout << __FUNCTION__ << std::endl;
    for (const auto& track : tracks.get<1>())
    {
        std::cout << track << std::endl;
    }
    std::cout << std::endl;
}


void print_by_album(const Tracks& tracks)
{
    std::cout << __FUNCTION__ << std::endl;
    for (const auto& track : tracks.get<2>())
    {
        std::cout << track << std::endl;
    }
    std::cout << std::endl;
}


int main()
{
    Tracks tracks;
    tracks.insert(Track{"A", "a"});
    tracks.insert(Track{"A", "d"});
    tracks.insert(Track{"B", "b"});
    tracks.insert(Track{"B", "e"});
    tracks.insert(Track{"C", "c"});
    tracks.insert(Track{"C", "f"});

    print_by_id(tracks);
    print_by_name(tracks);
    print_by_album(tracks);

    std::cout << "Albums: " << tracks.get<1>().size() << std::endl;
}

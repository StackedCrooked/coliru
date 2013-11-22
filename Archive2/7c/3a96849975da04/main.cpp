#include <deque>

// make compiler happy
struct Segment { bool empty() const; };
Segment read_segment();
std::deque<Segment> segment_queue;


// The fetch_segment function gets a segment from input data, stores it in a
// queue and returns the pointer of the segment in the queue.
// If no data was available then null is returned.


// fetch_segment_v1: nice and conservative
Segment* fetch_segment_v1()
{
    // read a data segment
    Segment segment = read_segment();
    
    // if no data is available an empty segment is returned
    if (segment.empty())
    {
        return nullptr;
    }
    
    // move to queue
    segment_queue.push_back(std::move(segment));
    
    // return pointer to the segment which now resides in the queue
    return &segment_queue.back();
}


// fetch_segment_v2: implicit move, but also a little weirdness
Segment* fetch_segment_v2()
{
    // read segment and add to queue (implicit move)
    segment_queue.push_back(read_segment());
    
    // check if valid
    if (segment_queue.back().empty())
    {
        segment_queue.pop_back();
        return nullptr;
    }
    return &segment_queue.back();
}


// fetch_segment_v3: overdoing it
Segment* fetch_segment_v3()
{
    // read segment and add to queue (implicit move)    
    segment_queue.push_back(read_segment());
    
    // remove from queue and return nullptr if segment was empty, else return pointer to segment in queue
    return segment_queue.back().empty() ? (segment_queue.pop_back(), nullptr) : &segment_queue.back();
}


void send()
{
    // unsent contains unsent segments
    // unacked contains sent segments which have not yet been acknowledged
    unacked.push_back(std::move(unsent.back()));
    unsent.pop_back();
    do_send(unacked.back()); // if this throws then unacked and unsent have invalid state
}
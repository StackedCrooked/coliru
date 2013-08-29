

void send()
{
    unacked.push_back(std::move(unsent.back()));
    unsent.pop_back();
    do_send(unacked.back()); // if this throws then unacked and unsent have invalid state
}
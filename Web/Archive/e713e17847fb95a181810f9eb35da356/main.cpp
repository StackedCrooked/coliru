

template<Continue>
void do_something(const Continue & cont)
{
    // do something in worker thread...
    cont();
}


std::future<Result> do_something()
{
    // do something in worker thread ...
}
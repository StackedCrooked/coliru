
void consumer()
{
    while (!quit)
    {
        std::function<void()> f;
        queue.pop(f);
        f();
    }
}
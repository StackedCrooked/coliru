{
    std::async(std::launch::async, []{ f(); });
    std::async(std::launch::async, []{ g(); });  // does not run until f() completes
}
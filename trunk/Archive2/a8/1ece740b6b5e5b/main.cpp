

// returns a future that is ready when the opengl thread reaches this
// work item
std::future<void> OpenGLThread::sync()
{
    std::shared_ptr<std::promise<void>> result(new std::promise<void>);
    
    // Assume emplace variadically forwards all of its arguments
    // to a std::function<void()> constructor, which is queued to
    // run in the opengl thread
    emplace([&,result] {
        result->set_value();
    });
    return result->get_future();
}



void close(Internal in, CloseCallback close_callback)
{
    auto make_safe = [=](CloseCallback callback)
    {
        return [=](Internal in)
        {
            try
            {
                callback(in);
            }
            catch (const std::exception& e)
            {
                std::cout << "caught: " << e.what() << std::endl;
            }
        };
    };
    
    
    close_callback = make_safe(close_callback);
    
    
    // work ...
    
    
    close_callback(in);
}


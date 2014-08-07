

struct Client
{
    // connects to server
    Client(std::string host, int port);
    
    // sends a request and returns result (blocking)
    std::string send(std::string) const;
};


int main()
{
    Client client("localhost", 12345);    
    std::cout << client.send("hello") << std::endl;
    std::cout << client.send("how are you") << std::endl;
    
    // ~Client should close the TCP connection and unblocks the io_service
}

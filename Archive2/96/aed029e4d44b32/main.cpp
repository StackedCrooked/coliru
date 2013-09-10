

// shared header for both server and client
struct Increment
{
    using result_type = int;
    using argument_type = int;
};


int main()
{
    // server side
    rpc_server server(9000);
    server.registerMethod<Increment>(int n) { return n + 1; }
    
    // client side
    rpc_client client("localhost", 9000);
    client.send<Increment>(2); // returns 3
}
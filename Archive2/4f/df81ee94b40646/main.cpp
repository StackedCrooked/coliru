

int main(int argc, char** argv)
{
    Arguments args(argc, argv);
    
    // v1
    std::string host = get(args, "--host");
    int port = get(args, "--port");
    
    // v2
    auto host = get<std::string>(args, "--host");
    auto port = get<int>(args, "--port");
}

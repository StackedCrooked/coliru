

struct PortCreate
{
    using ReturnType   = BBPort::Id;
    using ArgumentType = std::tuple<BBInterface::Id, std::string>;
};

int main()
{
    BBPort::Id id = send<PortCreate>(PortCreate::ArgumentType(id, "trunk-1-1"));
}

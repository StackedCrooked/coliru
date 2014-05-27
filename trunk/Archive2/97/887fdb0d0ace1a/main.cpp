#include "/Archive2/0d/a5c6abf40c82f9/main.cpp"

static
std::array<Session *, MAX_MAP_SERVERS> server_session;

auto iter_map_sessions() -> decltype(filter_iterator<Session *>(std::declval<std::array<Session *, MAX_MAP_SERVERS> *>()))
{
    return filter_iterator<Session *>(&server_session);
}

void frob(Session *)
{
}
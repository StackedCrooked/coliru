#include <memory>
#include <unordered_map>
#include <boost/asio.hpp>

namespace ip = boost::asio::ip;

/// @brief Mockup client.
class client:
  public std::enable_shared_from_this<client>
{
public:

  explicit client(ip::udp::endpoint endpoint)
    : endpoint_(endpoint)
  {}

  const ip::udp::endpoint& endpoint() const { return endpoint_; }

private:

  ip::udp::endpoint endpoint_;
};

/// @brief Basic class that manages clients.  Given an endpoint, the
///        associated client, if any, can be found.
class client_manager
{
private:

  // The underlying implementation used by the manager.
  using container_type = std::unordered_map<
    ip::udp::endpoint, std::shared_ptr<client>,
    std::size_t (*)(const ip::udp::endpoint&)>;

  /// @brief Return a hash value for the provided endpoint.
  static std::size_t get_hash(const ip::udp::endpoint& endpoint)
  {
    std::ostringstream stream;
    stream << endpoint;
    std::hash<std::string> hasher;
    return hasher(stream.str());
  }

public:

  using key_type = container_type::key_type;
  using mapped_type = container_type::mapped_type;

  /// @brief Constructor.
  client_manager()
    : clients_(0, &client_manager::get_hash)
  {}

// The public abstraction upon which the application will depend.
public:

  /// @brief Add a client to the manager.
  void add(mapped_type client)
  {
    clients_[client->endpoint()] = client;
  }

  /// @brief Given an endpoint, retrieve the associated client.  Return
  ///        an empty shared pointer if one is not found.
  mapped_type get(key_type key) const
  {
    auto result = clients_.find(key);
    return clients_.end() != result
      ? result->second // Found client.
      : mapped_type(); // No client found.
  }

private:

  container_type clients_;
};

int main()
{
  // Unique endpoints.
  ip::udp::endpoint endpoint1(ip::address::from_string("11.11.11.11"), 1111);
  ip::udp::endpoint endpoint2(ip::address::from_string("22.22.22.22"), 2222);
  ip::udp::endpoint endpoint3(ip::address::from_string("33.33.33.33"), 3333);

  // Create a client for each endpoint.
  auto client1 = std::make_shared<client>(endpoint1);
  auto client2 = std::make_shared<client>(endpoint2);
  auto client3 = std::make_shared<client>(endpoint3);

  // Add the clients to the manager.
  client_manager manager;
  manager.add(client1);
  manager.add(client2);
  manager.add(client3);

  // Locate a client based on the endpoint.
  auto client_result = manager.get(endpoint2);
  assert(client1 != client_result);
  assert(client2 == client_result);
  assert(client3 != client_result);
}
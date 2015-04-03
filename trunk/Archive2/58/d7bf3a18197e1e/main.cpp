#include <iostream>
#include <string>
#include <memory>

#include <fcntl.h>
#include <unistd.h>

struct file_descriptor
{
private:
  struct closer;

public:
  typedef int handle_type;
  typedef closer closer_type;

  constexpr static handle_type kInvalidHandle = -1;

public:
  file_descriptor(int handle = kInvalidHandle) : handle_{ handle } { }
  file_descriptor(std::nullptr_t) : file_descriptor{ } { }

  operator int&() { return handle_; }
  operator int() const { return handle_; }

  int& operator*() { return static_cast<int&>(*this); }
  int operator*() const { return static_cast<int>(*this); }

  bool operator==(const file_descriptor& other) const
  { return (handle_ == other.handle_); }

  bool operator!=(const file_descriptor& other) const
  { return !(*this == other); }

private:
  struct closer
  {
    typedef file_descriptor pointer;

    void operator()(pointer handle) const
    { ::close(*handle); }
  };

  int handle_;
};

using unique_file_ptr = std::unique_ptr<typename file_descriptor::handle_type,
                                        typename file_descriptor::closer_type>;

unique_file_ptr managed_open(const std::string& path)
{
  return { ::open(path.c_str(), O_RDWR), { } };
}

int main(int, char**)
{
  auto handle = managed_open("/dev/random");
  std::cout << "*handle      : " << *handle << std::endl;
  std::cout << "*handle.get(): " << *handle.get() << std::endl;
}

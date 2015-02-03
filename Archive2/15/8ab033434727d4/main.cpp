#pragma once

#include "IFoo.hpp"

#include <log4cxx/logger.h>

#include "FooSkeleton.hpp"
namespace barco
{
namespace platinum
{
namespace example
{

class FooService : public IFoo
{
public:

  using interface_t = IFoo;
  using skeleton_t  = FooSkeleton;

private:
  log4cxx::LoggerPtr m_logger;

public:
  FooService();
  FooService(FooService const &)               = delete;
  FooService & operator = (FooService const &) = delete;
  virtual ~FooService();

  void Ping() override;
  std::string Echo(std::string input) override;
  std::string Reverse(std::string input) override;
};

}
}
}
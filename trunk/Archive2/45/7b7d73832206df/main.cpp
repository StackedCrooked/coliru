#include<functional>
#include<string>
#include<memory>
#include<mutex>
#include<iostream>

class Config {

public:
  typedef std::function<void(std::string)> DupInitCB;

  static void init(std::string loc, DupInitCB err_cb);
  static Config& instance();

private:
  static Config& instance_helper(std::string loc = std::string(), DupInitCB err_cb = nullptr);
  
  std::string url;

  Config(std::string loc);
  Config(const Config& src) = delete;              // not implemented
  Config& operator=(const Config& right) = delete; // not implemented

public:
  std::string val(std::string key);
};

Config& Config::instance_helper(std::string loc, DupInitCB err_cb) {
  static std::unique_ptr<Config> cfg;
  static std::mutex init_mutex;

  if( !loc.empty() && err_cb != nullptr ) { // Initialize on request
    bool succeeded;
    { // scope of lock_guard
      std::lock_guard<std::mutex> lock(init_mutex);
      if (cfg != nullptr) {
        succeeded = false;
      } else {
        cfg.reset(new Config(loc));
        succeeded = true;
      }
    } // lock_guard is released here
    // error callback after releasing the lock`enter code here`
    if (!succeeded)
      err_cb(loc);
  }
  if (cfg == nullptr) throw std::logic_error("Requested uninitialized Config");
  return *cfg.get();
}

void Config::init(std::string loc, DupInitCB err_cb) {
  instance_helper(loc,err_cb);
}


Config& Config::instance() {
  return instance_helper();
}

Config::Config(std::string loc) : url(loc) {}

std::string Config::val(std::string key) {
  return key + " key requested at the location " + url;
}

int main()
{

  try {
    std::cout << Config::instance().val("Upstream") << std::endl;
    std::cerr << "Did not trow an exception when called an uninitialized Config." << std::endl;
    return 1;
  }
  catch (std::logic_error e) {
    std::cout << "Properly thrown an error when called an uninitialized Config." << std::endl;
  }
  catch (...) {
    std::cerr << "Thrown an unexpected exception when called an uninitialized Config." << std::endl;
    return 1;
  }

  Config::init(
    "http://cnf.local/dev",
    [](std::string loc){ std::cout << "Duplicate Config init (" << loc << ")" << std::endl; }
  );

  Config::init(
    "http://cnf.local/prod",
    [](std::string loc){ std::cout << "Duplicate Config init (" << loc << ")" << std::endl; }
  );

  std::cout << Config::instance().val("Upstream") << std::endl;
  return 0;
}
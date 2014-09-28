#include <iostream>
#include <unordered_map>

class ISettings {
 public:
  virtual ~ISettings() {}
  virtual std::string get(const std::string& key) const = 0;
};

class Settings : public ISettings {
 private:
  const ISettings* parent_settings_;
  std::unordered_map<std::string, std::string> settings_;

 public:
  Settings() : parent_settings_(nullptr) {}
  Settings(const ISettings* parent) : parent_settings_(parent) {}
  
  void set(const std::string& key, std::string value) {
    settings_[key] = std::move(value);
  }
  
  std::string get(const std::string& key) const override {
    auto found = settings_.find(key);
    if (found != settings_.end())
      return found->second;
    if (parent_settings_)
      return parent_settings_->get(key);
    return "";
  }
};

int main() {
  Settings global_settings;
  global_settings.set("ip", "127.0.0.1");
  global_settings.set("port", "8080");
  
  Settings local_settings(global_settings);
  local_settings.set("hostname", "example.com");
  local_settings.set("port", "12345"); // Overrride global settings
  
  std::cout << "ip: " << local_settings.get("ip") << "\n";
  std::cout << "port: " << local_settings.get("port") << "\n";
  std::cout << "hostname: " << local_settings.get("hostname") << "\n";
}

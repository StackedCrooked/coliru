#include <iostream>
#include <unordered_map>

class Settings {
  using SettingsType = std::unordered_map<std::string, std::string>;
 private:
  const SettingsType* local_;
  const SettingsType* global_;
 public:
  Settings(const SettingsType* local, const SettingsType* global) : local_(local), global_(global) {}
  virtual std::string get(const std::string& key) {
    if (local_) {
      auto element = local_->find(key);
      if (element != local_->end())
        return element->second; 
    }
    if (global_) {
      auto element = global_->find(key);
      if (element != global_->end())
        return element->second;
    }
    return "";
  }
};

int main() {
  std::unordered_map<std::string, std::string> global_settings;
  global_settings["ip"] = "127.0.0.1";
  global_settings["port"] = "8080";
  
  std::unordered_map<std::string, std::string> local_settings;  
  local_settings["hostname"] = "example.com";
  local_settings["port"] = "12345"; // Overrride global setting
  
  Settings settings(&global_settings, &local_settings);
  
  std::cout << "ip: " << settings.get("ip") << "\n";
  std::cout << "port: " << settings.get("port") << "\n";
  std::cout << "hostname: " << settings.get("hostname") << "\n";
}

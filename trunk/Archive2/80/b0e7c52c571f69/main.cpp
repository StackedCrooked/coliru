#include <iostream>
#include <ctime>
#include <chrono>

int main ()
{
  struct tm timeinfo;
  std::string buffer = "Thu, 9 Jan 2014 12:35:34";

  if (!strptime(buffer.c_str(), "%a, %d %b %Y %T", &timeinfo))
    std::cout << "Error.";
  std::cout << timeinfo.tm_sec << " " << timeinfo.tm_min 
            << " " << timeinfo.tm_hour << " " << timeinfo.tm_mday;
  auto tp = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo));
  auto now = std::chrono::system_clock::now();
  auto diff = now - tp;
  std::cout << std::chrono::duration_cast<std::chrono::seconds>(diff).count();
  return 0;
}
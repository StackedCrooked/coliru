#include <iostream>
#include <string>

std::string basename(const std::string& path)
{
    return path.substr(path.rfind('/') + 1);
}

std::string getProgramName(int argc, char * argv[]) {
  if (argc > 0) {
      std::string program_name(argv[0]);
      std::string::size_type last_separator = program_name.find_last_of('/');
      if (last_separator != std::string::npos && program_name.length() > last_separator + 1) {
          return program_name.substr(last_separator + 1);
      }
      return program_name;
  }
  return "my-default-program-name";
}

void test(const std::string& path)
{
    std::cout << "'" << path << "' => '" << basename(path) << "'\n";
}


void test2(int argc, char * argv[])
{
    std::cout << "'" << argv[0] << "' => '" << getProgramName(argc, argv) << "'" << std::endl;
}


int main(int argc, char * argv[])
{
    test2(argc, argv);
    test2(0, argv);
    char * values[1];
    values[0] = "test";
    test2(1, values);
    values[0] = "./test";
    test2(1, values);
    values[0] = "./bin/test";
    test2(1, values);
    values[0] = "/bin/test";
    test2(1, values);
    values[0] = "/";
    test2(1, values);
    values[0] = "/test/";
    test2(1, values);
    values[0] = "";
    test2(1, values);

    test("test");
    test("./test");
    test("./bin/test");
    test("/bin/test");
    test("/");
    test("/test/");
}
#include <memory>

typedef void* HANDLE;
const HANDLE INVALID_HANDLE_VALUE = 0;
void CloseHandle(HANDLE){}

struct FileResource 
{
    explicit FileResource(HANDLE hFile = INVALID_HANDLE_VALUE) 
        : _hFile(hFile, &::CloseHandle) { }
  private:
    std::unique_ptr<void, decltype(&::CloseHandle)> _hFile;
};

int main()
{
    auto hFile = FileResource {
        //CreateFile("main.cpp", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr)
    };
}

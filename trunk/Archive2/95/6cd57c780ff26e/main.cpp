#include <string>
#include <vector>

struct fileDetails
{
    std::string filePath;
    std::string fileName;
    std::string fileExt;

    void setFileDetails(std::string path);
};

void fileDetails::setFileDetails(std::string path)
{
    filePath = path.substr(0, path.find_last_of('\\'));
    fileExt = path.substr(path.find_last_of(".") + 1);
    fileName = path.substr(path.find_last_of('\\') + 1);
    fileName = fileName.substr(0, fileName.find_last_of('.'));
}

int main(int argc, char* argv[])
{
    std::vector<fileDetails> fileList;
    fileDetails fDet;

    for (int i = 0; i < argc; i++)
    {
        fDet.setFileDetails(argv[i]);
        fileList.push_back(fDet);
    }
}
#include <array>
#include <boost/optional.hpp>
#include <iostream>
#include <map>
#include <set>
#include <string>

using LoadableFile = std::string;

struct IndexContainer {
    typedef enum  { INSYNC, UPDATE, LOAD, EXTRA } FileType;

    typedef std::array<int32_t, 4>                          IndexQuartet;
    typedef std::map<IndexQuartet, std::set<LoadableFile> > IndexedFileInfo;
    typedef std::map<FileType, IndexedFileInfo>             FileInfo;

    inline void updateFileInfo(
        const FileType& rFileType,
        const IndexQuartet& rIndexQuartet,
        const std::set<LoadableFile>& rFileInfo
    )
    {
        mFileInfo[rFileType][rIndexQuartet].insert(rFileInfo.begin(), rFileInfo.end());
    }

    inline boost::optional<IndexedFileInfo const&> getFileInfo(const FileType& rFileType) const {
        auto match = mFileInfo.find(rFileType);
        if (match != mFileInfo.cend())
            return match->second;

        return boost::none;
    }

    inline friend std::ostream& operator << (std::ostream& os, const IndexContainer& rContainer) {
        for (const auto& next : rContainer.mFileInfo) {
            os << "FileType=" << next.first << std::endl; // the enum tupe

            // next.second is fileIndex &
            for (const auto& next1 : next.second) {
                const auto& quartet = next1.first;
                // print command quartet followed by loadable file
                for (const auto& next2 : next1.second) {
                    os  << "["
                        << quartet[0] << ","  // index1
                        << quartet[1] << ","  // index2
                        << quartet[2] << ","  // index3
                        << quartet[3] << "] " // index4
                        << next2 << std::endl;
                }
            }
        }
        return os;
    }
private:
    FileInfo mFileInfo;
};

int main() {
    IndexContainer container;

    container.updateFileInfo(IndexContainer::INSYNC, {{1,2,3,4}}, { "InSync1", "InSync2", "InSync3", "InSync4" });
    container.updateFileInfo(IndexContainer::UPDATE, {{1,2,5,6}}, { "Update1", "Update2", "Update3", "Update4" });
    container.updateFileInfo(IndexContainer::LOAD,   {{7,8,9,0}}, { "Load1",   "Load2",   "Load3",   "Load4"   });
    container.updateFileInfo(IndexContainer::EXTRA,  {{7,8,2,1}}, { "Extra1",  "Extra2",  "Extra3",  "Extra4"  });

    std::cout << container << std::endl;
}

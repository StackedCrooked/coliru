#include <set>
#include <map>
#include <string>
#include <tuple>
#include <iomanip>
#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

struct employee {
    employee(int id, const std::string& name)
        : id(id)
        , name(name)
    {}
    // natural ordering for set
    bool operator<(const employee& e) const {
        return id<e.id;
    }
    int id;
    std::string name;
    inline friend std::ostream& operator << (
        std::ostream& os, const employee& rEmp) {
        os << "id=" << rEmp.id << ", name=" << rEmp.name << std::endl;
        return os;
    }
};

// TYPEDEFS
// define a multiply indexed set with indices by id and name
// @TODO Use the multi_index_container to replace the 
// guts of the IndexContainer shown below
typedef boost::multi_index_container<
    employee,
    boost::multi_index::indexed_by<
        // sort by employee::operator<
        boost::multi_index::ordered_unique<boost::multi_index::identity<employee>>,
        // sort by less<string> on name
        boost::multi_index::ordered_non_unique<
        boost::multi_index::member<employee, std::string, &employee::name> >
    >
> employee_set;

struct LoadableFile {
    LoadableFile(const std::string& rName) 
        : mFileName(rName)
    {}
    
    inline bool operator<(const LoadableFile& rhs) const {
        return mFileName < rhs.mFileName;        
    }
    
    inline bool operator==(const LoadableFile& rhs) const {
        return mFileName == rhs.mFileName;        
    }
    
    inline friend std::ostream& operator << (
        std::ostream& os, const LoadableFile& rhs) {
        os << "FileName = " << rhs.mFileName;
        return os;
    }
    std::string mFileName;
};

class IndexContainer {
public:
    typedef enum  { INSYNC, UPDATE, LOAD, EXTRA } FileType;
    // 4 separate types of indeces defined 
    typedef std::tuple<int32_t, int32_t, int32_t, int32_t> IndexQuartet;

    // typedef showing relationship between IndexQuartet & its LoadableFiles
    typedef std::map<IndexQuartet, std::set<LoadableFile>> IndexedFileInfo;

    // define a mapping between the file type and its indexed files
    typedef std::map<FileType, IndexedFileInfo> FileInfo;

    // default constructor
    IndexContainer()
        : mFileInfo()
    {}

    // copy constructor
    IndexContainer(const IndexContainer& rhs)
        : mFileInfo(rhs.mFileInfo)
    {}

    // move constructor
    IndexContainer(IndexContainer&& rhs)
        : mFileInfo(std::move(rhs.mFileInfo))
    {}

    // non-throwing copy-and-swap idiom unified assignment
    inline IndexContainer& operator=(IndexContainer rhs) {
        rhs.swap(*this);
        return *this;
    }

    // non-throwing-swap idiom
    inline void swap(IndexContainer& rhs) {
        // enable ADL (not necessary in our case, but good practice)
        using std::swap;
        // swap base members
        //Base::swap(rhs);
        // swap members here
        swap(mFileInfo, rhs.mFileInfo);
    }

    // destructor
    virtual ~IndexContainer()
    {}

    // equality operator
    inline bool operator==(const IndexContainer& rhs) const {
        if (this != &rhs) {
            mFileInfo == rhs.mFileInfo;
        } else {
            return true;
        }
    }

    inline void updateFileInfo(
        const FileType& rFileType,
        const IndexQuartet& rIndexQuartet,
        const std::set<LoadableFile>& rFileInfo) {
        auto iter = mFileInfo.find(rFileType);
        if (iter == mFileInfo.cend()) {
            // temporary map object
            IndexedFileInfo fileInfo = {{rIndexQuartet, rFileInfo}};
            mFileInfo[rFileType] = std::move(fileInfo);
        } else { //potentially add a new KV pair or update 
            // the LoadableFiles if the quartet key matches
            auto iter1 = iter->second.find(rIndexQuartet);
            if (iter1 != iter->second.cend()) {
                // update the existing LoadableFile list
                iter1->second.insert(rFileInfo.begin(), rFileInfo.end());
            } else {
                iter->second[rIndexQuartet] = rFileInfo;
            }
        }
    }

    inline bool getFileInfo(
        const FileType& rFileType,
        IndexedFileInfo& rFileInfo) const {
        const auto& iter = mFileInfo.find(rFileType);
        if (iter != mFileInfo.cend()) {
            rFileInfo = iter->second;
            // indicate that we found some entries
            return true;
        } else { // unlikely but 
            // indicate nothing found and return
            return false;
        }
    }

    // let stream operators be friend functions instead of members!
    inline friend std::ostream& operator << (
        std::ostream& os, const IndexContainer& rContainer) {
        if (!rContainer.mFileInfo.empty()) {
            os << std::endl;
        }
        for (const auto& next : rContainer.mFileInfo) {
            os << "FileType=" << next.first << std::endl; // the enum tupe
            // next.second is fileIndex & 
            for (const auto& next1 : next.second) {
                // print command quartet followed by loadable file
                for (const auto& next2 : next1.second) {
                    const auto& quartet = next1.first;
                    os  << "[" 
                        << std::setw(2) << std::setfill('0') << std::dec << std::right
                        << std::get<0>(quartet) << ","  // index1
                        << std::setw(2) << std::setfill('0') << std::dec << std::right
                        << std::get<1>(quartet) << ","  // index2
                        << std::setw(2) << std::setfill('0') << std::dec << std::right
                        << std::get<2>(quartet) << ","  // index3
                        << std::setw(2) << std::setfill('0') << std::dec << std::right
                        << std::get<3>(quartet) << "] " // index4                        
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
    // this is the sort of behavior I need where I can specify multiple indexes
    employee_set employees;
    employees.insert(employee(1, "John"));
    employees.insert(employee(2, "Paul"));
    employees.insert(employee(3, "John"));
    // get a view to index #0 (id) - unique
    std::copy(employees.cbegin(), employees.cend(),
        std::ostream_iterator<employee>(std::cout));
    // get a view to index #1 (name)
    const employee_set::nth_index<1>::type& name_index = employees.get<1>();
    std::copy(name_index.begin(), name_index.end(),
        std::ostream_iterator<employee>(std::cout));    
    
    IndexContainer container;
    IndexContainer::IndexQuartet insyncIndexes(1,2,3,4);
    std::set<LoadableFile> insyncFiles = {
        LoadableFile("InSyncFile1"), LoadableFile("InSyncFile2"), 
        LoadableFile("InSyncFile3"), LoadableFile("InSyncFile4")
    };
    
    IndexContainer::IndexQuartet updateIndexes(1,2,5,6);
    std::set<LoadableFile> updateFiles = {
        LoadableFile("UpdateFile1"), LoadableFile("UpdateFile2"), 
        LoadableFile("UpdateFile3"), LoadableFile("UpdateFile4")
    };
    
    IndexContainer::IndexQuartet loadIndexes(7,8,9,0);
    std::set<LoadableFile> loadFiles = {
        LoadableFile("LoadFile1"), LoadableFile("LoadFile2"), 
        LoadableFile("LoadFile3"), LoadableFile("LoadFile4")
    };
    
    IndexContainer::IndexQuartet extraIndexes(7,8,2,1);
    std::set<LoadableFile> extraFiles = {
        LoadableFile("ExtraFile1"), LoadableFile("ExtraFile2"), 
        LoadableFile("ExtraFile3"), LoadableFile("ExtraFile4")
    };
    
    container.updateFileInfo(IndexContainer::INSYNC, insyncIndexes, insyncFiles);
    container.updateFileInfo(IndexContainer::UPDATE, updateIndexes, updateFiles);
    container.updateFileInfo(IndexContainer::LOAD,   loadIndexes, loadFiles);
    container.updateFileInfo(IndexContainer::EXTRA,  extraIndexes, extraFiles);
    std::cout << container << std::endl;
    
	return 0;
}


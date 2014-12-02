#include <fstream>
#include <iostream>
#include <string>

struct datatype {
    int key = 8;
    std::string name = "blank";
    int code = 0;
    double cost = 0;

    friend std::ostream& operator<<(std::ostream& os, datatype const& d) {
        return os << "-------------\n"
                  << "Index -1\n" // not useful anyways
                  << d.key << "\n"
                  << d.name << "\n"
                  << d.code << "\n"
                  << d.cost << "\n"
                  << "Useless statistics line for backwards compatibility\n"
                  << "-------------\n";
    }
    friend std::istream& operator>>(std::istream& is, datatype & d) {
        std::string header, trailer, indexline;

        if (
                std::getline(is, header) && header == "-------------"
            &&  std::getline(is, indexline) 
            &&  is >> d.key && is.ignore(1u<<10, '\n')
            &&  std::getline(is, d.name)
            &&  is >> d.code >> d.cost && is.ignore(1u<<10, '\n')
            &&  std::getline(is, trailer) // useless statistics line
            &&  std::getline(is, trailer) && trailer == "-------------")
        {
            return is;
        }

        throw "parse error"; // TODO exception class
    }
};

class Hash {
    private:
        static const int hashSize = 8;
        struct record : datatype {
            record(datatype const& rhs):datatype(rhs), next(NULL) {}
            record* next;
        };
        record* hashTable[hashSize];
    public:
        Hash();
        int hash(int key) const;
        void addRecord(datatype const& data);
        void saveRecords() const;
        datatype findRecord(int key) const;
        void load();
};

using namespace std;

Hash::Hash() {
    for(int i = 0; i < hashSize; i++) {
        hashTable[i] = new record(datatype{});
    }
}
void Hash::addRecord(datatype const& data) {
    int index = hash(data.key);
    if(hashTable[index]->key == 8) {
        *hashTable[index] = data;
    }
    else {
        record* newRecord = new record(data);
        newRecord->next = NULL;

        // find end
        record* ptr = hashTable[index];
        while(ptr->next != NULL) {
            ptr = ptr->next;
        }
        // append
        ptr->next = newRecord;
    }
}
int Hash::hash(int key) const {
    int index = key % 5;
    return index;
}
void Hash::saveRecords() const {
    std::ofstream recordsFile;
    recordsFile.open("records.dat");

    for(int i = 0; i < hashSize; i++) {
        recordsFile << hashTable[i];
    }
}

void Hash::load() {
    ifstream recordsFile("records.dat");
    datatype data;
    while (recordsFile >> data && data.key!=8)
        addRecord(data);
}

datatype Hash::findRecord(int key) const {
    int index = hash(key);
    record* ptr = hashTable[index];
    while(ptr != NULL) {
        if(ptr->key == key) {
            return *ptr;
        }
        ptr = ptr->next;
    }
    return {};
}

#if 0
using namespace std;

int main() {
    ifstream file;
    file.open("prog8.dat");
    if(!file.is_open()) {
        cerr << "Error opening file" << endl;
    }
    int index;
    int key;
    std::string name;
    int code;
    double cost;
    Hash hashObj;
    if(key != 8) {
        while(file >> key && file >> name && file >> code && file >> cost) {
            hashObj.addRecord(key, name, code, cost);
            hashObj.saveRecords();
            //hashObj.saveRecordsInIndex(index);
        }
    }
    file.close();
    return 0;
}
#else
using namespace std;

int main() {
    int key;
    Hash hashObj;
    hashObj.load();
    std::cout << "Please enter a key ";
    std::cin >> key;
    std::cout << hashObj.Hash::findRecord(key);

    return 0;
}
#endif

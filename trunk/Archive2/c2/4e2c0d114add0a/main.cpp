// listdir_recursive.c
// Osmar D. G
// Imprime el contenide de un directorio de manera recursiva

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdlib>
#include <cerrno>
#include <memory>

namespace {

    using dirent_entry = struct dirent;
    //using file_status = struct stat;

    constexpr const char * pwd=".";
    constexpr const char * parent_dir="..";

    class file_status {

        public:
        file_status()=default;
        explicit file_status(std::string file_name): file_name_{file_name} {
            init();
        }

        bool is_directory() { return (stat_buf_.st_mode & S_IFMT)==S_IFDIR; }
        bool is_equal(const char * dirname) { return file_name_.compare(dirname)==0;}

        private:

        void init(){ lstat(file_name_.c_str(), &stat_buf_); }
        std::string file_name_;
        struct stat stat_buf_;
    };

    auto list_directory(std::string dir, const size_t tab_size=0)->void{

        dirent_entry * entry;
        // cambiar por std::unique_ptr
        //auto dirptr = opendir(dir.c_str());
        // std::unique_ptr<DIR, decltype(closedir)> dirptr(opendir(dir.c_str()), closedir);
        std::unique_ptr< DIR, std::function< int(DIR*) > > dirptr( opendir(dir.c_str()), closedir ); // ***

        if(dirptr==nullptr){
            std::cerr << "No se pudo abrir el directorio...\n";
            exit(errno);
        }

        //Nos vamos al directorio
        chdir(dir.c_str());
        std::string tab (tab_size, ' ');
        while( (entry=readdir(dirptr.get())) not_eq nullptr) {

            file_status stats{entry->d_name};
            if(stats.is_directory()){

                if(stats.is_equal(pwd) or stats.is_equal(parent_dir))
                    continue;

                std::cout << tab << entry->d_name << std::endl;
                list_directory(entry->d_name, tab_size+2);

            }
            std::cout << tab << entry->d_name << std::endl;
        }

        chdir(parent_dir);
        //closedir(dirptr);
    }

}

int main(int argc, char** argv){

    using namespace std::literals::string_literals;

    const char* top_dir = nullptr;
    if(argc not_eq 2)
        top_dir = pwd;
    else
        top_dir=argv[1];

    std::cout << "Scaneando el directorio: "s + top_dir + "\n"s << std::flush;
    list_directory(top_dir);
    std::cout << "listo....." << std::endl;



}
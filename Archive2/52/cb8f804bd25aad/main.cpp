#pragma once 

#include <string>
#include <algorithm>
#include <sys/stat.h>
#include <sys/types.h>
#include <unordered_set>
#include <stdexcept>
#include <forward_list>
#include <regex>

#if defined (WIN32) //TODO implement std::filesystem whenever the commitee releases it.
    #if _MSC_VER >= 1600
        #include <Crosswind/private/dirent.h>
    #elif __MINGW32__
        #include <dirent.h>
    #endif
#else
#include <dirent.h>
#endif

namespace cw{

    class filesystem{
    public:
        static void add_directory(std::string directory, bool recursively = false){

            push_directory(directory);

            if(recursively){ add_recursively(directory); }

        }

		static bool exists (std::string filepath) {


            std::vector<std::string> path = split(filepath);

            //TODO test with Visual Studio.
            auto result = std::find_if(directories.begin(), directories.end(),
                    [&](std::string const& directory)  {
                        return path[0] != "" ?
                                is_file(directory + "/" + path[0] + "/" + path[1]) ||
                                is_dir(directory + "/" + path[0] + "/" + path[1])
                                :
                                is_file(directory + "/" + path[1]) ||
                                is_dir(directory + "/" + path[1]);
                    });

            if(result != std::end(directories)){
                return true;
            } else {
                return false;
            }
		}

        static std::string get_file_path(std::string& filepath){

            std::vector<std::string> path = split(filepath);

            if(exists(filepath)){


                auto result = std::find_if(directories.begin(), directories.end(),
                        [&](std::string const& directory)  {
                            //TODO test with Visual Studio.
                            if(path[0] != ""){
                                return is_file(directory + "/" + path[0] + "/" + path[1]);
                            } else {
                                return is_file(directory + "/" + path[1]);
                            }
                        });

                if(result != std::end(directories)){
                    return path[0] != "" ? *result + "/" + path[0] + "/" + path[1] : *result + "/" + path[1];
                } else {
                    throw std::runtime_error(path[1] + std::string(": Not a file."));
                }
            } else {
                throw std::runtime_error(path[1] + std::string(": Does not exist."));
            }
        }


    private:
        static bool is_file(const std::string& file){
            struct stat s;
            stat(file.c_str(), &s);
            return (s.st_mode & S_IFREG)!=0;
        }

        static bool is_dir(const std::string& dir){
            struct stat s;
            stat(dir.c_str(), &s);
            return (s.st_mode & S_IFDIR)!=0;
        }

        static std::vector<std::string> split(std::string filepath){ //TODO change to forward_list or faster impl.

            if(filepath.substr(filepath.size() - 1, filepath.size()).compare("/") == 0){
                filepath  = filepath.substr(0, filepath.size() - 1);
            }

            std::regex path_regex("^(.+/)(.+)$");
            std::smatch sm;

            std::vector<std::string> result(2);

            result[0] = "";
            result[1] = filepath;

            if (std::regex_match(filepath, sm, path_regex))
            {
                result[0] = sm[1];
                result[1] = sm[2];
            }

            return result;
        }

    private:
        static void push_directory(const std::string& directory){
            if(std::find(directories.begin(), directories.end(), directory) == directories.end())
            {
                directories.push_front(directory);
            }
        }


        static void add_recursively(std::string parent) {

            if(is_dir(parent)){

                push_directory(parent);

                if (DIR *dp = opendir(parent.c_str()))
                {
                    while (struct dirent *ep = readdir(dp))
                        if (ep->d_name[0] != '.')
                            add_recursively(parent + "/" + ep->d_name);
                    closedir(dp);
                }
                else
                    throw std::runtime_error(parent + std::string(": Couldn't open the directory."));
            }

        }


    private:
        static std::forward_list<std::string> directories;
	};

    //TODO make multithreaded
    std::forward_list<std::string> filesystem::directories;
}
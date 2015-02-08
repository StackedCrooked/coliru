#pragma once 


#include <Crosswind/graphics/texture.hpp>
#include <Crosswind/util/filesystem.hpp>

#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <regex>

namespace cw {

    class texture_pool{

    public:
		static std::shared_ptr<texture> loadTexture(std::string name,
                                                    double width, double height,
                                                    std::string path = "", bool create_copy = false){

            std::lock_guard<std::mutex> lock(pool_texture_mutex);

            std::shared_ptr<texture> rexture_result;
            std::string index = "_0";

            if(textures.find(name+index) != textures.end()) {

                if(create_copy){
                    bool match = false;
                    int replica_num = 0;

                    std::regex regex("^("+path+"+)_([0-9]*)$");

                    for(auto& t : textures){

                        std::smatch sm;
                        if(std::regex_match(t.first, sm, regex)){
                            replica_num = std::stoul(sm[2]);
                            ++replica_num;
                        }
                    }

                    rexture_result = std::shared_ptr<texture>
                            (new texture(filesystem::get_file_path(path), width, height));

                    name += "_" + replica_num;
                    textures[name] = rexture_result;


                } else {
                    rexture_result = textures[name];
                }

            } else {
                name += "_0";

                rexture_result = std::shared_ptr<texture>
                                (new texture(filesystem::get_file_path(path), width, height));

                textures[name] = rexture_result;
            }

            return rexture_result;
        }



        static std::shared_ptr<texture> getTexture(std::string name){
            std::lock_guard<std::mutex> lock(pool_texture_mutex);

            if(textures.find(name) != textures.end()) {

                return textures[name];

            } else {
                throw std::runtime_error(name + std::string(": Texture not loaded, load it first."));
            }

        }

	private:
		static std::unordered_map<std::string, std::shared_ptr<texture> > textures;
        static std::mutex pool_texture_mutex;

	};

    std::unordered_map<std::string, std::shared_ptr<texture> > texture_pool::textures;
    std::mutex texture_pool::pool_texture_mutex;
}


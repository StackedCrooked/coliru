#pragma once

#include <string> 
#include <thread> 
#include <atomic> 

#include <Crosswind/input/input_listener.hpp>
#include <Crosswind/graphics/object_xyz.hpp>
#include <Crosswind/graphics/texture.hpp>
#include <Crosswind/pools/texture_pool.hpp>
#include <Crosswind/events/delegate.hpp>

namespace cw{

    class widget: public input_listener, public virtual object_xyz{
    public:
        widget(){

            set_absolute_width(10.0);
            set_absolute_height(10.0);
            set_absolute_depth(10.0);

            switch_texture("current", std::shared_ptr<texture>(new texture(get_width(), get_height(), get_depth(), 4)));
            switch_texture("previous", get_texture("current"));

            set_text("");
            set_name("default");
            set_draggable(false);

            set_text_color(255, 255, 255);

            on_theme_set += [this](std::string theme){


                switch_texture("current",
                        texture_pool::loadTexture
                                (get_name(), get_width(), get_height(), theme + "/" + "textbox", true));

                switch_texture("previous", get_texture("current"));

            };

            set_theme("blue");

            on_attached += [this](std::shared_ptr<widget> element){

                element->set_absolute_width(element->get_width() * get_absolute_width());
                element->set_absolute_height(element->get_height() * get_absolute_height());
                element->set_absolute_depth(element->get_depth() * get_absolute_depth());
            };


            on_dimension_set += [this](std::shared_ptr<util::flag_container> flag_container){
                std::lock_guard<std::mutex> lock(texture_mutex);
                for(auto& texture : textures){
                    texture.second->resize(this->get_absolute_width(), this->get_absolute_height());
                }
            };

            on_mouse_down += [this](int x, int y, int button){

                if(!this->pressed.load()){
                    if(this->contains_xy(x, y)){
                        this->pressed.store(true);
                    }
                }

            };

            on_mouse_move += [this](int x, int y){

                if(this->pressed.load()){

                    if(this->get_draggable()){
                        this->set_x(x);
                        this->set_y(y);
                    }

                } else {
                    if (this->contains_xy(x, y)) {
                        //this->switch_texture("hover", textures["on"]); //TODO
                    }
                }

            };

            on_mouse_up += [this](int x, int y){

                if (pressed.load() && this->contains_xy(x, y)) {
                    on_clicked();
                }

                pressed.store(false);

            };

            on_mouse_down += [this](int x, int y, int button){

                for(auto& element : elements){
                    element->on_mouse_down(x, y, button);
                }

            };

            on_mouse_move += [this](int x, int y){

                for(auto& element : elements){
                    element->on_mouse_move(x, y);
                }

            };

            on_mouse_up += [this](int x, int y){

                for(auto& element : elements){
                    element->on_mouse_up(x, y);
                }

            };

            on_key_down += [this](int key){

                for(auto& element : elements){
                    element->on_key_down(key);
                }

            };

        }

        virtual void show(){
            set_visible(true);
            switch_texture("current", textures["previous"]);
            on_show();
        }

        virtual void hide(){
            set_visible(false);
            switch_texture("previous", textures["current"]);
            switch_texture("current", textures["blank"]);
            on_hide();
        }

        virtual void update(double delta){

            for(auto& element : elements){

                std::function<double(double, double)> percent_to_absolute = [](double percent, double dimension){

                    return dimension * percent;

                };

                double x_cord = percent_to_absolute(element->get_x(), this->get_absolute_width());
                double y_cord = percent_to_absolute(element->get_y(), this->get_absolute_height());

                double w_size = percent_to_absolute(element->get_width(), this->get_absolute_width());
                double h_size = percent_to_absolute(element->get_height(), this->get_absolute_height());

                element->set_absolute_x(this->get_absolute_x()+x_cord);
                element->set_absolute_y(this->get_absolute_y()+y_cord);

                element->set_absolute_width(w_size);
                element->set_absolute_height(h_size);

                element->update(delta);
            }

        }

        virtual void render(std::shared_ptr<texture> render_texture){

            if(get_texture("current")){

                get_texture("current")->draw_text(get_absolute_width()/2 ,
                        get_absolute_height()/2,
                        get_text(),
                        get_text_color());

                get_texture("current")->render_to_target(get_absolute_x(), get_absolute_y(), render_texture);
            }

            for(auto& element : elements){
                element->render(render_texture);
            }
        }

public:
        void set_text(std::string text){

            std::lock_guard<std::mutex> lock(text_mutex);
            text_string = text;

        }

        std::string get_text(){

            text_mutex.lock();
            std::string text = text_string;
            text_mutex.unlock();

            return text;
        }

        void set_text_color(unsigned char r, unsigned char g, unsigned char b){
            std::lock_guard<std::mutex> lock(color_mutex);
            text_color = std::shared_ptr<color_rgb>(new color_rgb(r, g, b));
        }

        std::shared_ptr<color_rgb> get_text_color(){
            color_mutex.lock();
            std::shared_ptr<color_rgb> color = text_color;
            color_mutex.unlock();

            return text_color;
        }

        void set_theme(std::string theme){

            std::lock_guard<std::mutex> lock(theme_mutex);
        	theme_string = theme;
            on_theme_set(theme);
        }

        std::string get_theme(){
        	std::string theme = "";

        	theme_mutex.lock();
        	theme = theme_string;
        	theme_mutex.unlock();

        	return theme;
        }

        void set_draggable(bool drag){
            draggable.store(drag);
        }

        bool get_draggable(){
            return draggable.load();
        }

        void switch_texture(std::string name, std::shared_ptr<texture> new_texture){
            std::lock_guard<std::mutex> lock(texture_mutex);
            textures[name] = new_texture;
        }

        std::shared_ptr<texture> get_texture(std::string name){
            std::shared_ptr<texture> texture;

            texture_mutex.lock();
            texture = textures[name];
            texture_mutex.unlock();

            return texture;
        }

        void attach(std::shared_ptr<widget> element) {
            std::lock_guard<std::mutex> lock(element_mutex);
            elements.push_back(element);
            on_attached(element);
        }

        void detach(std::shared_ptr<widget> element){
            std::lock_guard<std::mutex> lock(element_mutex);//TODO
        }



        delegate<void>         on_show;
        delegate<void>         on_hide;

        delegate<void> on_clicked;
        delegate<void, std::string> on_theme_set;

    protected:

        void set_name(std::string name){

            std::lock_guard<std::mutex> lock(name_mutex);
            name_string = name;

        }

        std::string get_name(){

            name_mutex.lock();
            std::string name = name_string;
            name_mutex.unlock();

            return name;
        }


    protected:
        std::mutex texture_mutex;
        std::map<std::string, std::shared_ptr<texture> > textures;

        delegate<void, std::shared_ptr<widget> > on_attached;

        std::vector<std::shared_ptr<widget>> elements; //Attached elements.


    private:    
        std::mutex text_mutex;
        std::string text_string;

        std::mutex name_mutex;
        std::string name_string;

        std::mutex color_mutex;
        std::shared_ptr<color_rgb> text_color;

        std::mutex theme_mutex;
        std::string theme_string;

        std::mutex element_mutex;

        std::atomic<bool> draggable;

        std::atomic<bool> pressed;

    };


}
#pragma once

#include <CImg/CImg.h>

#include <string>
#include <memory>
#include <mutex>

#include <Crosswind/gui/widgets/detail/display_target.hpp>
#include <Crosswind/graphics/color_rgb.hpp>

namespace cw{

    class texture{
    public:

        texture(double width, double height, double depth, double bpp){
            texture_data = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>(width, height, depth, bpp, 255));

            texture_clear_buffer = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>(width, height, depth, bpp, 255));

        }

        texture(std::string path, double width, double height){
            texture_data = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>());
            texture_clear_buffer = std::shared_ptr<cimg_library::CImg<unsigned char> >
                    (new cimg_library::CImg<unsigned char>());

            texture_data->assign(path.c_str());
            texture_clear_buffer->assign(path.c_str());
        }

        void clear(){
            std::lock_guard<std::mutex> lock(texture_mutex);
            (*texture_data).fill(0);
            (*texture_clear_buffer).fill(0);

        }


        void draw_text(double x, double y, std::string text, std::shared_ptr<color_rgb> color){
            std::lock_guard<std::mutex> lock(texture_mutex);
            (*texture_data) = (*texture_clear_buffer);

//            const unsigned char black[] = { 0, 0, 0};

            cimg_library::CImg<unsigned char> imgtext =
                    cimg_library::CImg<unsigned char>().draw_text(0,0,text.c_str(), color->data(), NULL).
                            resize(-100,-100, 1, 4);

            //@TODO move this to widget.hpp and implement alignment.
            (*texture_data).draw_image(x - imgtext.width()/2,
                                       y - imgtext.height()/2,
                                       0,
                                       0,
                                       imgtext,
                                       imgtext.get_channel(3),
                                       1,
                                       255);

        }

        void resize(double width, double height){
            std::lock_guard<std::mutex> lock(texture_mutex);
            (*texture_data).resize(width, height, -100, -100, 3); //Linear interpolation works best for PNG
            (*texture_clear_buffer).resize(width, height, -100, -100, 3);
        }

        void render_to_target(double x, double y, std::shared_ptr<texture> target){

            std::lock_guard<std::mutex> lock(texture_mutex);
            target->texture_data->draw_image(x, y, 0, 0, *texture_data);

        }

        void render_to_display(std::shared_ptr<display_target> target){
            std::lock_guard<std::mutex> lock(texture_mutex);
            target->display(*texture_data);
        }

	private:
        std::mutex texture_mutex;
        std::shared_ptr<cimg_library::CImg<unsigned char> > texture_data;
        std::shared_ptr<cimg_library::CImg<unsigned char> > texture_clear_buffer; //Exact copy without modifications.

    };

}
	
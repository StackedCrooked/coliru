#pragma once

#include <Crosswind/gui/widgets/detail/widget.hpp>
#include <Crosswind/gui/widgets/window.hpp>
#include <Crosswind/gui/widgets/button.hpp>
#include <Crosswind/gui/widgets/textbox.hpp>
#include <Crosswind/gui/widgets/label.hpp>
#include <Crosswind/gui/widgets/panel.hpp>


/* TODO
    std::shared_ptr<cw::widget> window(new cw::window([](){
        std::shared_ptr<cw::util::flag_container> flags(new cw::util::flag_container());
        //  flags->set<cw::window::window_flags>(cw::window::window_flags::MULTITHREADED);
        return flags;
    }()));

    */ 

namespace cw{
    class widget_pool{
	public:
		template<typename T>
	    static std::shared_ptr<widget> create(double x, double y, double w, double h, std::string theme){ //TODO init flags here. 

	        std::shared_ptr<widget> ptr(new T());
	        ptr->set_x(x);
	        ptr->set_y(y);
	        ptr->set_width(w);
	        ptr->set_height(h);
	        ptr->set_theme(theme);

	        return ptr;
	    }
	};
}
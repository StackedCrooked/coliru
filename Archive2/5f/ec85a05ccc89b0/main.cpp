#include <crosswind/engine.hpp>

#include <characters/sonic.hpp>
#include <zones/green_hill.hpp>


int main()
{
    auto engine = std::make_shared<cw::engine>();
    engine->core->filesystem->add_directory("assets", true);

    auto scene = std::make_shared<game::zones::green_hill>();
    auto actor = std::make_shared<game::characters::sonic>();

    scene->set_name("my_scene");

    scene->add_actor("default", actor);

    engine->stage->add_scene(scene);
    engine->stage->load_scene("my_scene");

    engine->run();
}

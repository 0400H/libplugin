#include <string>
#include <typeinfo>
#include <vector>
#include <unordered_map>
#include <any>

#include "libplugin/factory.hpp"
#include "cpp/utils.hpp"

#include "hello/hello.hpp"
#include "world/world.hpp"

TEST_CASE("factory") {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");

    auto hello_path = "hello/libtesthello.so";
    auto world_path = "world/libtestworld.so";

    auto factory = std::make_shared<libplugin::factory>(hello_path, RTLD_LAZY);
    factory->open(world_path, RTLD_LAZY, 2);

    auto hello_func = FACTORY_VIEW_SYMBOL(factory, hello, hello_path, 0);
    auto world_func = FACTORY_VIEW_SYMBOL(factory, world, world_path, 0);
    auto plugin_func = FACTORY_VIEW_SYMBOL(factory, plugin, world_path, 1);

    CHECK( (hello_func() == "hello") );
    CHECK( (world_func() == "world") );
    CHECK( (plugin_func() == "hello plugin") );
}

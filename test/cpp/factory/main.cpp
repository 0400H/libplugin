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
    auto hello_path = "hello/libtesthello.so";
    auto world_path = "world/libtestworld.so";

    auto factory = std::make_shared<libplugin::factory>(hello_path, RTLD_LAZY);
    factory->open(world_path, RTLD_LAZY, libplugin::F_L_STRICT);

    // Automatic symbol type derivation using macro FACTORY_VIEW_SYMBOL
    auto hello_func = FACTORY_VIEW_SYMBOL(factory, hello, hello_path, libplugin::F_S_STRICT);
    auto world_func = FACTORY_VIEW_SYMBOL(factory, world, world_path, libplugin::F_S_STRICT);
    auto plugin_func = FACTORY_VIEW_SYMBOL(factory, plugin, world_path, libplugin::F_S_FUZZY);

    CHECK( (hello_func() == "hello") );
    CHECK( (world_func() == "world") );
    CHECK( (plugin_func() == "hello plugin") );
}

#include "cpp/utils.hpp"
#include "my_plugin/my_plugin.hpp"

int main() {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");

    // create my_plugin instance
    auto plugin_impl = std::make_shared<my_plugin>();

    // get symbol registry from instance
    auto registry = plugin_impl->view_all();

    // print symbols of registry
    for (auto& pair : registry->view_all()) {
        spdlog::info("registered symbol -> {}.", pair.first);
    };

    // get symbol from registry
    // Fuzzy search symbol by using macro REGISTRY_VIEW_SYMBOL
    auto hello_func = *REGISTRY_VIEW_SYMBOL(registry, hello);
    auto world_func = *REGISTRY_VIEW_SYMBOL(registry, world);
    // Factory mode search symbol by using two macro
    auto hello_plugin_identity = IDENTITY("hello/libhello.so", plugin);
    auto hello_plugin_func = *ANY_CAST_OBJ(&plugin, registry->view(hello_plugin_identity));
    auto world_plugin_func = *REGISTRY_VIEW_RAW_SYMBOL(registry, plugin, "world/libworld.so");

    // run func
    hello_func();
    world_func();
    hello_plugin_func();
    world_plugin_func();

    // unload symbol if u want
    registry->unload_symbol(SYMBOL_TYPE(hello));
    registry->unload_symbol("world/libworld.so@plugin@void ()");
    registry->unload_symbol(hello_plugin_identity);

    // print symbols of registry
    for (auto& pair : registry->view_all()) {
        spdlog::info("registered symbol -> {}.", pair.first);
    };
    return 0;
}

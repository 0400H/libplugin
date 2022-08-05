#include "cpp/utils.hpp"
#include "my_plugin/my_plugin.hpp"

int main() {
    // create my_plugin instance
    auto plugin_impl = std::make_shared<my_plugin>();

    // get symbol registry from instance
    auto registry = plugin_impl->view_all();

    // print symbols in registry
    for (auto& pair : registry->view_all()) {
        spdlog::info("registered symbol -> {}.", pair.first);
    };

    // get symbol from registry
    auto hello_path = "hello/libhello.so";
    auto world_path = "world/libworld.so";
    // Fuzzy search symbol by using macro REGISTRY_VIEW_N_SYMBOL
    auto hello_func = *REGISTRY_VIEW_N_SYMBOL(registry, hello);
    auto world_func = *REGISTRY_VIEW_N_SYMBOL(registry, world);
    // Factory mode search symbol by using two macro
    auto hello_plugin_func = *REGISTRY_VIEW_L_SYMBOL(registry, plugin, hello_path);
    auto world_plugin_func = *REGISTRY_VIEW_L_SYMBOL(registry, plugin, world_path);

    // run func
    hello_func();
    world_func();
    hello_plugin_func();
    world_plugin_func();

    // unload symbol if u want
    registry->unload_symbol(N_IDENTITY(hello));
    registry->unload_symbol(L_IDENTITY(hello_path, plugin));
    registry->unload_symbol("plugin#void ()@world/libworld.so");

    // print symbols in registry
    for (auto& pair : registry->view_all()) {
        spdlog::info("registered symbol -> {}.", pair.first);
    };
    return 0;
}

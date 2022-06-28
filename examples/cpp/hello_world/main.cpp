#include "cpp/utils.hpp"
#include "my_plugin/my_plugin.hpp"

int main() {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");

    auto plugin_impl = std::make_shared<my_plugin>();
    auto registry = plugin_impl->view_all();

    for (auto& pair : registry->view_all()) {
        spdlog::info("registered symbol: {}.", pair.first);
    };

    auto hello_func = REGISTRY_VIEW_SYMBOL(registry, hello);
    auto world_func = REGISTRY_VIEW_SYMBOL(registry, world);
    auto hello_plugin_func = REGISTRY_VIEW_RAW_SYMBOL(registry, plugin, "hello/libhello.so");
    auto world_plugin_func = *ANY_CAST_SYMBOL(&plugin, registry->view("world/libworld.so@plugin@void ()"));

    hello_func();
    world_func();
    hello_plugin_func();
    world_plugin_func();
    return 0;
}

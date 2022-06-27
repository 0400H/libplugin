#include "cpp/utils.hpp"
#include "my_plugin/my_plugin.hpp"

int main() {
    spdlog::info(fmt::format("{}.", "i love c++"));

    auto plugin_impl = std::make_shared<my_plugin>();
    plugin_impl->init();

    // for (auto &func : plugin_impl.iter()) {
    //     spdlog::info(fmt::format("register func: {}.", func.name()));
    // };

    // auto hello = plugin_impl["hello"]("type1");
    // auto world = plugin_impl["world"]("type1", "type2");

    // hello(arg1);
    // world(arg1, arg2);

    plugin_impl->release();
    return 0;
}

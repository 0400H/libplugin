#include "my_plugin.hpp"

int mian() {
    auto plugin_impl = std::make_shared<my_plugin>();
    plugin_impl->init();
    plugin_impl->export("libmyplugin.a");
    plugin_impl->export("libmyplugin.so");
    plugin_impl->close();
};

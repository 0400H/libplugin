#include <spdlog/spdlog.h>

#include "libplugin/registry.hpp"

#include "my_plugin.hpp"

my_plugin::my_plugin() {
    this->init();
};

my_plugin::~my_plugin() {
    this->release();
};

libplugin::status my_plugin::release() {
    return this->unload_all();
};

libplugin::status my_plugin::init() {
    // create func registry
    this->registry = std::make_shared<libplugin::registry>();

    // load libs
    this->hello_lib = std::make_shared<libplugin::library>("hello/libhello.so", RTLD_LAZY);
    this->world_lib = std::make_shared<libplugin::library>("world/libworld.so", RTLD_LAZY);

    // get symbol_map from lib
    libplugin::symbol_map hello_symbol = {
        get_library_type_pair(this->hello_lib, hello),
        get_library_type_pair(this->hello_lib, plugin),
    };

    libplugin::symbol_map world_symbol = {
        get_library_type_pair(this->world_lib, world),
        get_library_type_pair(this->world_lib, plugin),
    };

    // register symbols
    // symbols, override mode
    spdlog::trace("register_symbols(hello_symbol)");
    auto status = this->registry->register_symbols(hello_symbol, 1);
    libplugin::print_status(status);

    spdlog::trace("register_symbols(world_symbol)");
    status |= this->registry->register_symbols(world_symbol, 0);
    libplugin::print_status(status);

    // get func container from registry
    auto container = this->registry->view_all();
    return status;
};

libplugin::status my_plugin::unload_all() {
    auto status_code = libplugin::S_Success;
    if (this->registry) {
        status_code |= this->registry->unload_all();
    };
    // if (this->factory) {
    //     status_code |= this->factory.unload_all();
    // };
    if (this->hello_lib) {
        status_code |= this->hello_lib->close();
    };
    if (this->world_lib) {
        status_code |= this->world_lib->close();
    };
    libplugin::parse_status(status_code);
    return status_code;
};


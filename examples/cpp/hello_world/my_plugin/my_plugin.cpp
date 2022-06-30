#include <spdlog/spdlog.h>
#include "libplugin/registry.hpp"
#include "my_plugin.hpp"

my_plugin::my_plugin() {
    this->init();
};

my_plugin::~my_plugin() {
    this->release();
};

void my_plugin::release() {
    this->unload_all();
};

libplugin::status my_plugin::init() {
    // create func registry
    this->registry = std::make_shared<libplugin::registry>();

    // create library factory
    this->factory = std::make_shared<libplugin::factory>();

    // load libs to factory
    auto hello_path = "hello/libhello.so";
    auto world_path = "world/libworld.so";
    this->factory->open("hello/libhello.so", RTLD_LAZY, 0);
    this->factory->open("world/libworld.so", RTLD_LAZY, 1);

    // get symbols map
    libplugin::symbol_map hello_world_symbol = {
        FACTORY_SYMBOL_PAIR(this->factory, hello, hello_path, 0),
        FACTORY_SYMBOL_PAIR(this->factory, world, hello_path, 1),
        FACTORY_IDENTITY_PAIR(this->factory, plugin, hello_path),
        FACTORY_IDENTITY_PAIR(this->factory, plugin, world_path),
    };

    auto status = this->registry->register_symbols(hello_world_symbol, 0);

    /*
    this->hello_lib = std::make_shared<libplugin::library>("hello/libhello.so", RTLD_LAZY);
    this->world_lib = std::make_shared<libplugin::library>("world/libworld.so", RTLD_LAZY);

    // get symbol_map
    libplugin::symbol_map hello_symbol = {
        LIB_SYMBOL_PAIR(this->hello_lib, hello),
        LIB_SYMBOL_PAIR(this->hello_lib, plugin),
    };
    libplugin::symbol_map world_symbol = {
        LIB_SYMBOL_PAIR(this->world_lib, world),
        LIB_SYMBOL_PAIR(this->world_lib, plugin),
    };

    // register symbols
    spdlog::trace("register_symbols(hello_symbol)");
    auto status = this->registry->register_symbols(hello_symbol, 1);
    spdlog::trace("register_symbols(world_symbol)");
    status |= this->registry->register_symbols(world_symbol, 0);
    libplugin::print_status(status);
    */

    // get registry(symbol container)
    auto container = this->registry->view_all();
    libplugin::parse_status(status);
    return status;
};

void my_plugin::unload_all() {
    if (this->registry) {
        this->registry->unload_all();
    };
    if (this->factory) {
        this->factory->unload_all();
    };
    // if (this->hello_lib) {
    //     this->hello_lib->close();
    // };
    // if (this->world_lib) {
    //     this->world_lib->close();
    // };
};


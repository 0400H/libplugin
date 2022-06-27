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

    // get func table from lib
    libplugin::symbols hello_symbol = {
        { type_name(hello), this->hello_lib->get_func(macro_to_string(hello).c_str()) },
    };

    libplugin::symbols world_symbol = {
        { type_name(world), this->hello_lib->get_func(macro_to_string(world).c_str()) },
    };

    // register funcs
    // func list, override mode, strict mode
    auto status = this->registry->register_args(hello_symbol, 0);
    print_status(status);

    status |= this->registry->register_args(world_symbol, 1);
    print_status(status);

    status = this->registry->unload_arg(type_name(hello));
    print_status(status);

    status |= this->registry->unload_arg(type_name(world));
    print_status(status);

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
    // if (this->hello_lib) {
    //     status_code |= this->hello_lib->unload_all();
    // };
    // if (this->world_lib) {
    //     status_code |= this->world_lib->unload_all();
    // };
    libplugin::parse_status(status_code);
    return status_code;
};


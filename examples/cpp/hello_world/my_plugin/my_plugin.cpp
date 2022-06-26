#include "my_plugin.hpp"

#include "hello/hello.hpp"
#include "world/world.hpp"

class my_plugin : public libplugin::plugin_base {
public:
    hello_world_plugin() {
        this->init();
    };

    ~hello_world_plugin() {
        this->release();
    };

    libplugin::status init() {
        // load libs
        this->hello = std::make_shared<libplugin::library>("hello.so");
        this->world = std::make_shared<libplugin::library>("world.so");

        // get func table from lib
        auto hello_func_list = this->hello->list_all();
        auto world_func_list = std::make_shared<libplugin::func_list>();
        world_func_list.parse(
            {
                "func" : ["type1", "type2"],
            };
        );

        // create func register
        this->register = std::make_shared<libplugin::register>();

        // get func into register
        // func list, override mode, strict mode
        auto status = this->reg->register_funcs(hello_func_list, false, false);
        this->reg->parse_status(status);

        status = this->reg->register_funcs(world_func_list, true, false);
        this->reg->parse_status(status);

        status = this->reg.unload_func();
        this->reg->parse_status(status);

        status = this->reg->register_func(hello_world_func, false, true);
        this->reg->parse_status(status);

        // get func container from register
        this->funcs = this->reg->list_all();

        // list funcs in func container
        this->funcs->list_all();

        return status;
    };

    libplugin::status release() {
        return this->unload_all();
    };

    libplugin::status unload_all() {
        libplugin::status status = ;
        if (this->funcs) {
            status = this->funcs.unload_all();
            this->funcs->parse_status(status);
        };
        if (this->reg) {
            status = this->reg.unload_all();
            this->reg->parse_status(status);
        };
        if (this->hello) {
            status = this->hello.unload_all();
        };
        if (this->world) {
            status = this->world.unload_all();
        };
    };

    libplugin::status export_lib() {
        libplugin::status status = ;
        if (this->funcs) {
            status = this->funcs.unload_all();
            this->funcs->parse_status(status);
        };
        if (this->reg) {
            status = this->reg.unload_all();
            this->reg->parse_status(status);
        };
        if (this->hello) {
            status = this->hello.unload_all();
        };
        if (this->world) {
            status = this->world.unload_all();
        };
    };

private:
    std::shared_ptr<libplugin::container> funcs = nullptr;
    std::shared_ptr<libplugin::register> reg = nullptr;
    // std::shared_ptr<libplugin::factory> hello = nullptr;
    std::shared_ptr<libplugin::library> hello = nullptr;
    std::shared_ptr<libplugin::library> world = nullptr;
};

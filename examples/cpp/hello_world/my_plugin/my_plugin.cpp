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
        // create func register
        this->registry = std::make_shared<libplugin::registry>();

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

        // register funcs
        // func list, override mode, strict mode
        auto status = this->reg->register_funcs(hello_func_list, false, false);
        print_status(status);

        status |= this->reg->register_funcs(world_func_list, true, false);
        print_status(status);

        status = this->reg.unload_func();
        print_status(status);

        status |= this->reg->register_func(hello_world_func, false, true);
        print_status(status);

        // get func container from register
        this->funcs = this->reg->list_all();

        // list funcs in func container
        this->funcs->list_all();
        return status;
    };

    libplugin::status unload_all() {
        auto status_code = S_Success;
        if (this->registry) {
            status_code |= this->reg.unload_all();
        };
        if (this->factory) {
            status_code |= this->factory.unload_all();
        };
        if (this->hello) {
            status_code |= this->hello.unload_all();
        };
        if (this->world) {
            status_code |= this->world.unload_all();
        };
        this->parse_status(status_code);
        return status_code;
    };

    libplugin::status release() {
        return this->unload_all();
    };

private:
    std::shared_ptr<libplugin::container> funcs = nullptr;
    std::shared_ptr<libplugin::register> reg = nullptr;
    // std::shared_ptr<libplugin::factory> hello = nullptr;
    std::shared_ptr<libplugin::library> hello = nullptr;
    std::shared_ptr<libplugin::library> world = nullptr;
};

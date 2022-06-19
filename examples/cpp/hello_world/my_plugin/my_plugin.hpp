#include <spdlog/spdlog.h>
#include <fmt/format.h>
// #include <fmt/ranges.h>
// #include <fmt/color.h>
// #include <fmt/chrono.h>
// #include <fmt/compile.h>
// #include <fmt/ostream.h>
// #include <fmt/printf.h>
// #include <fmt/os.h>

#include "plugin/container.hpp"
#include "plugin/register.hpp"
#include "plugin/library.hpp"
#include "plugin/status.hpp"

#include "hello/hello.hpp"
#include "world/world.hpp"

class my_plugin : public plugin_base {
public:
    hello_world_plugin() {
        this->init();
    };

    ~hello_world_plugin() {
        this->close();
    };

    plugin::status open() {
        // load libs
        this->hello = std::make_shared<plugin::library>("hello.so");
        this->world = std::make_shared<plugin::library>("world.so");

        // get func table from lib
        auto hello_func_list = this->hello->list_all();
        auto world_func_list = std::make_shared<plugin::func_list>();
        world_func_list.parse(
            {
                "func" : ["type1", "type2"],
            };
        );

        // create func register
        this->register = std::make_shared<plugin::register>();

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

    plugin::status unload_all() {
        plugin::status status = ;
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

    plugin::status close() {
        return this->unload_all();
    };

private:
    std::shared_ptr<plugin::container> funcs = nullptr;
    std::shared_ptr<plugin::register> reg = nullptr;
    // std::shared_ptr<plugin::factory> hello = nullptr;
    std::shared_ptr<plugin::library> hello = nullptr;
    std::shared_ptr<plugin::library> world = nullptr;
};

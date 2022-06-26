#include "libplugin/container.hpp"
#include "libplugin/register.hpp"
#include "libplugin/plugin.hpp"
#include "libplugin/factory.hpp"
#include "libplugin/library.hpp"
#include "libplugin/status.hpp"

class my_plugin : public libplugin::plugin_base {
public:
    hello_world_plugin();

    ~hello_world_plugin();

    libplugin::status init();

    libplugin::status release();

    libplugin::status unload_all();

    libplugin::status export_lib();

private:
    std::shared_ptr<libplugin::container> funcs = nullptr;
    std::shared_ptr<libplugin::register> reg = nullptr;
    // std::shared_ptr<libplugin::factory> hello = nullptr;
    std::shared_ptr<libplugin::library> hello = nullptr;
    std::shared_ptr<libplugin::library> world = nullptr;
};

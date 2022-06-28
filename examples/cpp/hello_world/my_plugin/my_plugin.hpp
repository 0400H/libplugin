#include <memory>

#include "libplugin/plugin.hpp"
#include "libplugin/factory.hpp"
#include "libplugin/library.hpp"

#include "hello/hello.hpp"
#include "world/world.hpp"

class my_plugin : public libplugin::plugin_base {
public:
    my_plugin();
    ~my_plugin();
    libplugin::status init() override;
    void release() override;
    void unload_all();
private:
    std::shared_ptr<libplugin::factory> factory = nullptr;
    // std::shared_ptr<libplugin::library> hello_lib = nullptr;
    // std::shared_ptr<libplugin::library> world_lib = nullptr;
};

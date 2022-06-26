#include <memory>

#include "libplugin/plugin.hpp"
#include "libplugin/factory.hpp"
#include "libplugin/library.hpp"

class my_plugin : public libplugin::plugin_base {
public:
    libplugin::status init() override;
    libplugin::status release() override;
    libplugin::status unload_all();
private:
    std::shared_ptr<libplugin::factory> factory = nullptr;
    std::shared_ptr<libplugin::library> hello = nullptr;
    std::shared_ptr<libplugin::library> world = nullptr;
};

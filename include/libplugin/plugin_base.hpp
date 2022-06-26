#include <memory>
#include <string>

#include "container.hpp"
#include "registry.hpp"
#include "status.hpp"

namespace libplugin {

class plugin_base {
public:
    virtual libplugin::status init() = 0;
    virtual libplugin::status release() = 0;
    virtual libplugin::status export_lib(const char *);
    virtual std::shared_ptr<libplugin::container> plugin_base::get_container();
protected:
    std::shared_ptr<libplugin::registry> registry = nullptr;
};

}
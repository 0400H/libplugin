#ifndef LIBPLUGIN_REGISTRY_H
#define LIBPLUGIN_REGISTRY_H

#include <memory>

#include "libplugin/container.hpp"
#include "libplugin/status.hpp"

namespace libplugin {

class registry {
public:
    status register_func();
    status register_funcs();
    status unload_func();
    status unload_funcs();
    std::shared_ptr<container> view_all();
private:
    std::shared_ptr<container> container;
};

}

#endif
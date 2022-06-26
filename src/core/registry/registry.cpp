#include "libplugin/registry.hpp"

namespace libplugin {

    status registry::register_func() {
        return S_Success;
    };

    status registry::register_funcs() {
        return S_Success;
    };

    status registry::unload_func() {
        return S_Success;
    };

    status registry::unload_funcs() {
        return S_Success;
    };

    std::shared_ptr<container> registry::view_all() {
        return this->container;
    };

}
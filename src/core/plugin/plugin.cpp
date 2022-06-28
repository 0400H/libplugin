#include <string>

#include "libplugin/plugin.hpp"


namespace libplugin {

    status plugin_base::export_lib(const char * lib_path) {
        return S_Success;
    };

    std::shared_ptr<registry> plugin_base::view_all() {
        return this->registry;
    };

}

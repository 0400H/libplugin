#include <string>

#include "libplugin/plugin_base.hpp"


namespace libplugin {

    status plugin_base::export_lib(const char * lib_path) {
        status ret;
        return ret;
    };

    std::shared_ptr<registry> plugin_base::view_all() {
        return this->registry;
    };

}

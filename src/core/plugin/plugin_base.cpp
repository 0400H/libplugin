#include <string>

#include "libplugin/plugin_base.hpp"

// typedef std::unordered_map<std::string, std::any> container;

namespace libplugin {

    status plugin_base::export_lib(const char * lib_path) {
        status ret;
        return ret;
    };

    std::unordered_map<std::string, std::any> plugin_base::view_all() {
        return this->registry->view_all();
    };

}

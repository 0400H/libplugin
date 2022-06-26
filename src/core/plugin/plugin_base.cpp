#include <string>

#include "libplugin/plugin_base.hpp"

namespace libplugin {

   libplugin::status plugin_base::export_lib(const char * lib_path) {
        status ret;
        return ret;
    };

    std::shared_ptr<libplugin::container> plugin_base::get_container() {
        return this->registry->get_container();
    };

}

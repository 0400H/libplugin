#ifndef LIBPLUGIN_PLUGIN_BASE_H
#define LIBPLUGIN_PLUGIN_BASE_H

#include <memory>
#include <string>

#include "registry.hpp"
#include "status.hpp"

namespace libplugin {

class plugin_base {
public:
    virtual status init() = 0;
    virtual status release() = 0;
    virtual status export_lib(const char *);
    virtual std::unordered_map<std::string, std::any> view_all();
protected:
    std::shared_ptr<registry> registry = nullptr;
};

}

#endif
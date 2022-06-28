#ifndef LIBPLUGIN_PLUGIN_H
#define LIBPLUGIN_PLUGIN_H

#include "registry.hpp"
#include "factory.hpp"

namespace libplugin {

class plugin_base {
public:
    virtual status init() = 0;
    virtual void release() = 0;
    virtual status export_lib(const char *);
    virtual std::shared_ptr<registry> view_all();
protected:
    std::shared_ptr<registry> registry = nullptr;
};

}

#endif
#include "libplugin/registry.hpp"
#include "core/utils.hpp"
#include <cxxabi.h>

namespace libplugin {

status registry::register_symbol(std::string type, std::any arg, int override_mode) {
    spdlog::debug("Register symbol -> {}.", type);
    auto ret = S_Success;
    if (override_mode == 0) {
        spdlog::debug("Override policy: Allowed to override.");
        this->container[type] = arg;
    } else if (override_mode == 1) {
        spdlog::debug("Override policy: Not allowed to override.");
        if (this->container.count(type) == 0) {
            this->container[type] = arg;
        }
    } else {
        spdlog::debug("Override policy: Not allowed to override, if find then return error.");
        if (this->container.count(type) == 0) {
            this->container[type] = arg;
        } else {
            ret = S_Failed;
        };
    };
    return ret;
};

status registry::register_symbols(symbol_map& args, int mode) {
    for (auto& arg : args) {
        this->register_symbol(arg.first, arg.second, mode);
    };
    return S_Success;
};

status registry::unload_symbol(std::string type) {
    this->container.erase(type);
    return S_Success;
};

status registry::unload_symbols(std::vector<std::string> types) {
    for (auto type : types) {
        this->unload_symbol(type);
    };
    return S_Success;
};

status registry::unload_all() {
    for (auto pair : this->container) {
        this->unload_symbol(pair.first);
    };
    return S_Success;
};

std::any registry::view(std::string type) {
    return this->container.at(type);
};

symbol_map registry::view_all() {
    return this->container;
};

std::string cxx_demangle(const char* name) {
    char buffer[1024] = {0};
    size_t size = sizeof(buffer);
    int status;
    char *ret;
    try {
        ret = abi::__cxa_demangle(name, buffer, &size, &status);
        if(ret) {
            return std::string(ret);
        } else {
            return name;
        }
    } catch(...) {
        return name;
    }
    return name;
}

}

#include "libplugin/registry.hpp"
#include <cxxabi.h>
#include <spdlog/spdlog.h>

namespace libplugin {

status registry::register_arg(std::string type, std::any arg, int mode) {
    auto ret = S_Success;
    if (mode == 0) {
        spdlog::debug("Allowed to override -> {}", type);
        this->container[type] = arg;
    } else if (mode == 1) {
        spdlog::debug("Not allowed to override -> {}", type);
        if (this->container.count(type) == 0) {
            this->container[type] = arg;
        }
    } else {
        spdlog::debug("Not allowed to override and return error -> {} ", type);
        if (this->container.count(type) == 0) {
            this->container[type] = arg;
        } else {
            ret = S_Failed;
        };
    };
    return ret;
};

status registry::register_args(symbols& args, int mode) {
    for (auto& arg : args) {
        this->register_arg(arg.first, arg.second, mode);
    };
    return S_Success;
};

status registry::unload_arg(std::string type) {
    this->container.erase(type);
    return S_Success;
};

status registry::unload_args(std::vector<std::string> types) {
    for (auto type : types) {
        this->unload_arg(type);
    };
    return S_Success;
};

status registry::unload_all() {
    for (auto pair : this->container) {
        this->unload_arg(pair.first);
    };
    return S_Success;
};

std::any registry::view(std::string type) {
    return this->container.at(type);
};

symbols registry::view_all() {
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

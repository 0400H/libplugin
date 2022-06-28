#include "libplugin/registry.hpp"
#include "core/utils.hpp"

namespace libplugin {

status registry::register_symbol(std::string type, std::any arg, int override_mode) {
    spdlog::trace("Register symbol -> {}.", type);
    auto ret = S_Success;
    if (override_mode == 0) {
        spdlog::trace("Override policy: Allowed to override.");
        this->container[type] = arg;
    } else if (override_mode == 1) {
        spdlog::trace("Override policy: Not allowed to override.");
        if (this->container.count(type) == 0) {
            this->container[type] = arg;
        }
    } else {
        spdlog::trace("Override policy: Not allowed to override, if find then return error.");
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

void registry::unload_symbol(std::string type) {
    this->container.erase(type);
};

void registry::unload_symbols(std::vector<std::string> types) {
    for (auto type : types) {
        this->unload_symbol(type);
    };
};

void registry::unload_all() {
    this->container.clear();
};

std::any registry::view(std::string type) {
    return this->container.at(type);
};

symbol_map registry::view_all() {
    return this->container;
};

}

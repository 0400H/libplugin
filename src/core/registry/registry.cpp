#include "libplugin/registry.hpp"
#include "core/utils.hpp"

namespace libplugin {

status registry::register_symbol(std::string type, std::any arg, int policy) {
    spdlog::trace("registry::register_symbol({}, arg, {}).", type, policy);
    auto ret = S_Success;
    if (policy == R_OVERRIDE) {
        spdlog::trace("registry override policy: allowed to override.");
        this->container[type] = arg;
    } else if (policy == R_FORBID) {
        spdlog::trace("registry override policy: not allowed to override.");
        if (this->container.count(type) == 0) {
            this->container[type] = arg;
        } else {
            spdlog::trace("Can not register {}.", type);
        }
    } else {
        spdlog::trace("registry override policy: not allowed to override, if find then return error.");
        if (this->container.count(type) == 0) {
            this->container[type] = arg;
        } else {
            spdlog::trace("registry can not register {}.", type);
            ret = S_Failed;
        };
    };
    return ret;
};

status registry::register_symbols(symbol_table args, int policy) {
    for (auto arg : args) {
        this->register_symbol(arg.first, arg.second, policy);
    };
    return S_Success;
};

void registry::unload_symbol(std::string type) {
    spdlog::trace("registry::unload_symbol({}).", type);
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

symbol_table registry::view_all() {
    return this->container;
};

}

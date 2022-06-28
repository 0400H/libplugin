#include "libplugin/factory.hpp"
#include "core/utils.hpp"

namespace libplugin {

factory::factory(std::string lib_path, int lib_mode) {
    this->open(lib_path, lib_mode, 0);
};

status factory::open(std::string lib_path, int lib_mode, int policy) {
    spdlog::trace("factory::open({}, {}, {})", lib_path, lib_mode, policy);
    auto ret = S_Success;

    auto lib_ptr = std::make_shared<libplugin::library>();
    ret |= lib_ptr->open(lib_path.c_str(), lib_mode);

    if (ret != S_Success) {
        return ret;
    } else {
        if (policy == 0) {
            spdlog::trace("Factory policy: Load as default");
            this->bucket[lib_path] = lib_ptr;
        } else if (policy == 1) {
            spdlog::trace("Factory policy: Load with override");
            this->bucket[lib_path] = lib_ptr;
        } else if (policy == 2) {
            spdlog::trace("Factory policy: Load without override");
            if (this->bucket.count(lib_path) == 0) {
                this->bucket[lib_path] = lib_ptr;
            } else {
                ret = S_Failed;
            };
        } else {
            ret = S_UnInitialized;
        }
    }
    return ret;
};

status factory::close(std::string lib_path) {
    this->bucket.erase(lib_path);
    return S_Success;
};

status factory::close() {
    this->bucket.clear();
    return S_Success;
};

status factory::has_lib(std::string lib_path) {
    auto ret = S_Success;
    if (this->bucket.count(lib_path) == 0) {
        spdlog::trace("Not find lib -> {}", lib_path);
        ret = S_InvalidValue;
    }
    return ret;
};
status factory::has_lib() {
    auto ret = S_Success;
    if (this->bucket.empty()) {
        ret = S_Failed;
    }
    return ret;
};

status factory::has_default_lib() {
    return this->has_lib(this->default_lib);
};

status factory::as_default(std::string lib_path) {
    auto ret = this->has_lib(lib_path);
    if (!ret){
        this->default_lib = lib_path;
    }
    return ret;
};

std::any factory::view(std::string lib_path, std::string symbol) {
    if (this->has_lib(lib_path)) {
        return std::any(nullptr);
    } else {
        auto arg = this->bucket.at(lib_path)->get_symbol(symbol.c_str());
        return std::any(arg);
    };
};

std::any factory::view(std::string lib_path, std::string symbol, int mode) {
    spdlog::trace("factory::view({}, {}, {})", lib_path, symbol, mode);
    if (mode == 0) {
        spdlog::trace("Find symbol mode: find symbol from target lib");
        return this->view(lib_path, symbol);
    } else {
        spdlog::trace("Find symbol mode: find symbol from any lib");
        auto arg = this->bucket[this->default_lib]->get_symbol(symbol.c_str());
        if (arg) {
            return std::any(arg);
        } else {
            for (auto & pair : this->bucket) {
                if (pair.first != lib_path) {
                    auto arg = pair.second->get_symbol(symbol.c_str());
                    if (arg) {
                        return std::any(arg);
                    };
                };
            };
            std::any(nullptr);
        };
    };
};

}

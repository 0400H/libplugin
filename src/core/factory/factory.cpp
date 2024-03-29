#include "libplugin/factory.hpp"
#include "core/utils.hpp"

namespace libplugin {

factory::factory() {};

factory::factory(std::string lib_path, int lib_mode) {
    this->open(lib_path, lib_mode, 0);
};

status factory::open(std::string lib_path, int lib_mode, int policy) {
    std::lock_guard<std::mutex> lock(this->mtx);
    spdlog::trace("factory::open({}, {}, {})", lib_path, lib_mode, policy);
    auto ret = S_Success;

    auto lib_ptr = std::make_shared<libplugin::library>();
    ret |= lib_ptr->open(lib_path.c_str(), lib_mode);

    if (ret != S_Success) {
        return ret;
    } else {
        if (policy == F_L_DEFAULT) {
            spdlog::trace("factory library policy: load as default");
            this->bucket[lib_path] = lib_ptr;
            this->default_lib = lib_path;
        } else if (policy == F_L_OVERRIDE) {
            spdlog::trace("factory library policy: load and override");
            this->bucket[lib_path] = lib_ptr;
        } else if (policy == F_L_STRICT) {
            spdlog::trace("factory library policy: load without override");
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

void factory::close(std::string lib_path) {
    std::lock_guard<std::mutex> lock(this->mtx);
    spdlog::trace("factory::close({}).", lib_path);
    this->bucket.erase(lib_path);
};

void factory::unload_all() {
    std::lock_guard<std::mutex> lock(this->mtx);
    this->bucket.clear();
};

bool factory::has_lib(std::string lib_path) {
    bool ret = true;
    if (this->bucket.count(lib_path) == 0) {
        spdlog::trace("factory not find lib -> {}", lib_path);
        ret = false;
    }
    return ret;
};
bool factory::has_lib() {
    bool ret = true;
    if (this->bucket.empty()) {
        ret = false;
    }
    return ret;
};

bool factory::has_default_lib() {
    return this->has_lib(this->default_lib);
};

status factory::as_default(std::string lib_path) {
    auto ret = S_Success;
    if (this->has_lib(lib_path)){
        std::lock_guard<std::mutex> lock(this->mtx);
        this->default_lib = lib_path;
    } else {
        ret = S_InvalidValue;
    };
    return ret;
};

void* factory::view(std::string symbol, std::string lib_path, int policy) {
    std::lock_guard<std::mutex> lock(this->mtx);
    spdlog::trace("factory::view({}, {}, {})", symbol, lib_path, policy);
    if (policy == F_S_STRICT) {
        spdlog::trace("factory symbol policy: find from target lib");
        if (this->has_lib(lib_path)) {
            return this->bucket.at(lib_path)->view(symbol.c_str());
        } else {
            return nullptr;
        };
    } else {
        spdlog::trace("factory symbol policy: find from any lib");
        if (this->has_lib(this->default_lib)) {
            auto arg = this->bucket[this->default_lib]->view(symbol.c_str());
            if (arg) {
                return arg;
            } else {
                for (auto & pair : this->bucket) {
                    if (pair.first != lib_path) {
                        auto arg = pair.second->view(symbol.c_str());
                        if (arg) {
                            return arg;
                        };
                    };
                };
                return nullptr;
            };
        } else {
            return nullptr;
        };
    };
};

void* factory::view(std::string symbol, std::string lib_path) {
    return this->view(symbol, lib_path, F_S_STRICT);
};

void* factory::view(std::string symbol) {
    return this->view(symbol, this->default_lib);
};

std::vector<void*> factory::view(std::vector<std::string> symbols, std::string lib_path, int policy) {
    std::vector<void*> ret;
    for (auto & symbol : symbols) {
        ret.emplace_back(this->view(symbol, lib_path, policy));
    };
    return ret;
};

std::vector<void*> factory::view(std::vector<std::string> symbols, std::string lib_path) {
    return this->view(symbols, lib_path, 0);
};

std::vector<void*> factory::view(std::vector<std::string> symbols) {
    return this->view(symbols, this->default_lib);
};

}

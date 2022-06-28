#include "libplugin/library.hpp"

#include "dl_sal.hpp"
#include "core/utils.hpp"

#include <string>
#include <stdexcept>
#include <cxxabi.h>

namespace libplugin {

library::library() : handle(nullptr) {};

library::library(const char* file, int mode) : handle(nullptr) {
    if (this->open(file, mode) != S_Success) {
        std::runtime_error("Can not open library!");
    };
}

library::~library() {
    this->close();
}

status library::open(const char* file, int mode) {
    std::lock_guard<std::mutex> lock(this->mutex);
    auto ret = S_Success;
    if (file) {
        spdlog::trace("library::open({}, {}).", file, mode);
        this->handle = dlopen(file, mode);
        auto error = dlerror();
        if (error != nullptr || this->handle == nullptr) {
            spdlog::error("dlopen({}, {}) error: {}.", file, mode, error);
            ret = S_Failed;
        }
    } else {
        spdlog::error("wrong null file pointer!");
        ret = S_InvalidValue;
    };
    return ret;
}

status library::close() {
    std::lock_guard<std::mutex> lock(this->mutex);
    if (this->handle) {
        dlclose(handle);
    }
    this->handle = nullptr;
    return S_Success;
}

void* library::get_symbol(const char* name) {
    std::lock_guard<std::mutex> lock(this->mutex);
    spdlog::trace("library::get_symbol({})", name);
    auto func = dlsym(this->handle, name);
    auto error = dlerror();
    if (error != nullptr || this->handle == nullptr) {
        spdlog::trace("Not find symbol {}, error: {}", name, error);
        return nullptr;
    } else {
        return func;
    }
}

void* library::get_handle() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->handle;
}

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

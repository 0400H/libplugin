#include "libplugin/library.hpp"

#include "dl_sal.hpp"
#include "core/utils.hpp"

#include <string>
#include <stdexcept>
#include <cxxabi.h>

namespace libplugin {

library::library() : ptr(nullptr) {};

library::library(const char* file, int mode) : ptr(nullptr) {
    if (this->open(file, mode) != S_Success) {
        std::runtime_error("Can not open library!");
    };
}

library::~library() {
    this->close();
}

status library::open(const char* file, int mode) {
    std::lock_guard<std::mutex> lock(this->mtx);
    spdlog::trace("library::open({}, {}).", file, mode);
    auto ret = S_Success;
    if (file) {
        this->name = std::string(file);
        this->ptr = dlopen(file, mode);
        auto error = dlerror();
        if (error != nullptr || this->ptr == nullptr) {
            spdlog::error("dlopen({}, {}) error: {}.", file, mode, error);
            ret = S_Failed;
        }
    } else {
        spdlog::error("wrong null file pointer!");
        ret = S_InvalidValue;
    }
    return ret;
}

void library::close() {
    std::lock_guard<std::mutex> lock(this->mtx);
    spdlog::trace("library::close() -> {}.", this->name);
    if (this->ptr) {
        dlclose(this->ptr);
    }
    this->ptr = nullptr;
}

void* library::view(const char* name) {
    std::lock_guard<std::mutex> lock(this->mtx);
    spdlog::trace("library::view({})", name);
    auto func = dlsym(this->ptr, name);
    auto error = dlerror();
    if (error != nullptr || this->ptr == nullptr) {
        spdlog::trace("Not find symbol {}, error: {}", name, error);
        return nullptr;
    } else {
        return func;
    }
}

void* library::handle() {
    std::lock_guard<std::mutex> lock(this->mtx);
    return this->ptr;
}

std::string cxx_demangle(const char* name) {
    char buffer[1024] = {0};
    size_t size = sizeof(buffer);
    int status;
    char *ret;
    try {
        ret = abi::__cxa_demangle(name, buffer, &size, &status);
        if(ret) {
            return ret;
        } else {
            return name;
        }
    } catch(...) {
        return name;
    }
    return name;
}

}

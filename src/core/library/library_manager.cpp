#include "libplugin/library.hpp"

#include "library_sal.hpp"
#include "core/utils.hpp"

#include <string>
#include <stdexcept>

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
        spdlog::debug(fmt::format("library::open({}, {}).", file, mode));
        this->handle = dlopen(file, mode);
        auto error = dlerror();
        if (error != nullptr || this->handle == nullptr) {
            spdlog::error(fmt::format("dlopen({}, {}) error: {}.", file, mode, error));
            ret = S_Failed;
        }
    } else {
        spdlog::error("wrong null file pointer!");
        ret = S_InvalidValue;
    };
    return ret;
}

void library::close() {
    std::lock_guard<std::mutex> lock(this->mutex);
    if (this->handle) {
        dlclose(handle);
    }
    this->handle = nullptr;
}

void* library::get_func(const char* name) {
    std::lock_guard<std::mutex> lock(this->mutex);
    auto func = dlsym(this->handle, name);
    auto error = dlerror();
    if (error != nullptr || this->handle == nullptr) {
        auto err_msg = fmt::format("dlsym({}, {}) error: {}.", this->handle, name, error);
        throw std::runtime_error(err_msg);
        return nullptr;
    } else {
        return func;
    }
}

void* library::get_handle() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return this->handle;
}

}

#include "libplugin/library.hpp"
#include "library_sal.hpp"

#include <string>
#include <stdexcept>

namespace libplugin {

library::library() : handle(nullptr) {};

library::library(const char* file, int mode) : handle(nullptr) {
    set_logger_level();
    this->open(file, mode);
}

library::~library() {
    this->close();
}

void library::open(const char* file, int mode) {
    std::lock_guard<std::mutex> lock(this->mutex);
    spdlog::debug(fmt::format("library::open({}, {}).", file, mode));
    this->handle = dlopen(file, mode);
    auto error = dlerror();
    if (error != nullptr || this->handle == nullptr) {
        auto err_msg = fmt::format("dlopen({}, {}) error: {}.", file, mode, error);
        spdlog::error(err_msg);
        throw std::runtime_error(err_msg);
    }
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
        throw std::runtime_error("dlsym " + std::string(name) + " error, " + std::string(error));
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

#include "libplugin/container.hpp"

#include <cxxabi.h>

namespace libplugin {
// https://blog.csdn.net/only_1/article/details/80285212
// https://blog.csdn.net/CaspianSea/article/details/46616819

void container::insert(std::string type, std::any arg) {
    this->map[type] = arg;
};

std::any container::get(std::string type) {
    return this->map.at(type);
};

std::string cxx_demangle(const char* name) {
    char buffer[1024] = {0};
    size_t size = sizeof(buffer);
    int status;
    char *ret;
    try {
        ret =  abi::__cxa_demangle(name, buffer, &size, &status);
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
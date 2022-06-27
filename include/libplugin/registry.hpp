#ifndef LIBPLUGIN_REGISTRY_H
#define LIBPLUGIN_REGISTRY_H

#include <unordered_map>
#include <memory>
#include <any>

#include "libplugin/status.hpp"

namespace libplugin {
// https://blog.csdn.net/only_1/article/details/80285212
// https://blog.csdn.net/CaspianSea/article/details/46616819

class registry {
public:
    status register_arg(std::string, std::any, int);
    status register_args(std::unordered_map<std::string, std::any>, int);
    status unload_arg(std::string);
    status unload_args(std::vector<std::string>);
    std::any view(std::string);
    std::unordered_map<std::string, std::any> view_all();
private:
    std::unordered_map<std::string, std::any> container;
};

std::string cxx_demangle(const char*);

}

#define macro_to_string(x) std::string(#x)

#define type_name(type_arg) \
    macro_to_string(type_arg) + "@" + libplugin::cxx_demangle(typeid(type_arg).name())

#define type_cast(type_arg, any_arg) \
    std::any_cast<decltype(type_arg)>(any_arg)

#define register_type_object(registry, type_arg) \
    registry->register_arg(typename(type_arg), &type_arg)

#define view_type_object(registry, type_arg) \
    type_cast(&type_arg, registry->view(typename(type_arg)))

#endif

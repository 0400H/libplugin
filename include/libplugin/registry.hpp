#ifndef LIBPLUGIN_REGISTRY_H
#define LIBPLUGIN_REGISTRY_H

#include <unordered_map>
#include <memory>
#include <any>

#include "libplugin/status.hpp"

namespace libplugin {
// https://blog.csdn.net/only_1/article/details/80285212
// https://blog.csdn.net/CaspianSea/article/details/46616819

typedef std::unordered_map<std::string, std::any> symbols;

class registry {
public:
    status register_arg(std::string, std::any, int);
    status register_args(symbols &, int);
    status unload_arg(std::string);
    status unload_args(std::vector<std::string>);
    status unload_all();
    std::any view(std::string);
    symbols view_all();
private:
    symbols container;
};

std::string cxx_demangle(const char*);

}

#define macro_to_string(x) \
    std::string(#x)

#define type_name(type_arg) \
    macro_to_string(type_arg) + "@" + libplugin::cxx_demangle(typeid(type_arg).name())

#define any_type_cast(type_arg, any_arg) \
    std::any_cast<decltype(type_arg)>(any_arg)

#define reinterpret_type_cast(type_arg, any_arg) \
    reinterpret_cast<decltype(type_arg)>(any_arg)

#define register_type_object(registry, type_arg) \
    registry->register_arg(type_name(type_arg), &type_arg)

#define get_any_type_object(registry, type_arg) \
    *any_type_cast(&type_arg, registry->view(type_name(type_arg)))

#define get_library_type_object(library, type_arg) \
    reinterpret_type_cast(&type_arg, library->get_func(macro_to_string(type_arg).c_str()))

#define get_library_type_pair(library, type_arg) \
    { type_name(type_arg), get_library_type_object(library, type_arg) }

#endif

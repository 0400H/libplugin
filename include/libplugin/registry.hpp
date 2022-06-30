#ifndef LIBPLUGIN_REGISTRY_H
#define LIBPLUGIN_REGISTRY_H

#include <unordered_map>
#include <memory>

#include "library.hpp"

namespace libplugin {
// https://blog.csdn.net/only_1/article/details/80285212
// https://blog.csdn.net/CaspianSea/article/details/46616819

typedef std::unordered_map<std::string, std::any> symbol_map;

class registry {
public:
    status register_symbol(std::string, std::any, int);
    status register_symbols(symbol_map &, int);
    void unload_symbol(std::string);
    void unload_symbols(std::vector<std::string>);
    void unload_all();
    std::any view(std::string);
    symbol_map view_all();
protected:
    symbol_map container;
};

}

#define REGISTRY_REGISTER_ARG(REGISTRY, SYMBOL_NAME, OBJ) \
    REGISTRY->register_symbol(SYMBOL_TYPE(SYMBOL_NAME), &OBJ)

#define REGISTRY_VIEW_SYMBOL(REGISTRY, SYMBOL_NAME) \
    *ANY_CAST(&SYMBOL_NAME, REGISTRY->view(SYMBOL_TYPE(SYMBOL_NAME)))

#define REGISTRY_VIEW_RAW_SYMBOL(REGISTRY, SYMBOL_NAME, LIB_NAME) \
    *ANY_CAST(&SYMBOL_NAME, REGISTRY->view(IDENTITY(LIB_NAME, SYMBOL_NAME)))

#endif

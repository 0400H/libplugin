#ifndef LIBPLUGIN_REGISTRY_H
#define LIBPLUGIN_REGISTRY_H

#include <unordered_map>
#include <memory>

#include "library.hpp"

namespace libplugin {
// https://blog.csdn.net/only_1/article/details/80285212
// https://blog.csdn.net/CaspianSea/article/details/46616819

typedef std::unordered_map<std::string, std::any> symbol_table;

class registry {
public:
    status register_symbol(std::string, std::any, int);
    status register_symbols(symbol_table, int);
    void unload_symbol(std::string);
    void unload_symbols(std::vector<std::string>);
    void unload_all();
    std::any view(std::string);
    symbol_table view_all();
protected:
    symbol_table container;
};

}

#define REGISTRY_REGISTER_SYMBOL(REGISTRY, SYMBOL, POLICY) \
    REGISTRY->register_symbol(SYMBOL_TYPE(SYMBOL), &SYMBOL, POLICY)

#define REGISTRY_VIEW_SYMBOL(REGISTRY, SYMBOL) \
    ANY_CAST_OBJ(&SYMBOL, REGISTRY->view(SYMBOL_TYPE(SYMBOL)))

#define REGISTRY_VIEW_RAW_SYMBOL(REGISTRY, SYMBOL, LIBRARY) \
    ANY_CAST_OBJ(&SYMBOL, REGISTRY->view(IDENTITY(LIBRARY, SYMBOL)))

#endif

#ifndef LIBPLUGIN_FACTORY_H
#define LIBPLUGIN_FACTORY_H

#include <memory>
#include <unordered_map>

#include "library.hpp"

namespace libplugin {

typedef std::unordered_map<std::string, std::shared_ptr<library>>  library_map;

enum factory_library_policy {
    F_L_DEFAULT = 0,        // load library as default
    F_L_OVERRIDE = 1,       // load library with override
    F_L_STRICT = 2,         // load library without override
};

enum factory_symbol_policy {
    F_S_STRICT = 0,        // find symbol from target lib
    F_S_FUZZY = 1,         // find symbol from any lib
};

class factory {
public:
    factory();
    factory(std::string, int);

    status open(std::string, int, int);
    void close(std::string);

    void unload_all();

    bool has_lib(std::string);
    bool has_lib();
    bool has_default_lib();

    status as_default(std::string);

    void* view(std::string, std::string, int);
    void* view(std::string, std::string);
    void* view(std::string);

    std::vector<void*> view(std::vector<std::string>, std::string, int);
    std::vector<void*> view(std::vector<std::string>, std::string);
    std::vector<void*> view(std::vector<std::string>);

protected:
    std::string default_lib;
    library_map bucket;
    std::mutex mtx;
};

}

#define FACTORY_VIEW_SYMBOL(FACTORY, SYMBOL, LIBRARY, POLICY) \
    R_CAST_OBJ(&SYMBOL, FACTORY->view(TO_STRING(SYMBOL), LIBRARY, POLICY))

#define FACTORY_N_SYMBOL_PAIR(FACTORY, SYMBOL, LIBRARY, POLICY) \
    { N_IDENTITY(SYMBOL), FACTORY_VIEW_SYMBOL(FACTORY, SYMBOL, LIBRARY, POLICY) }

#define FACTORY_L_SYMBOL_PAIR(FACTORY, SYMBOL, LIBRARY) \
    { L_IDENTITY(LIBRARY, SYMBOL), FACTORY_VIEW_SYMBOL(FACTORY, SYMBOL, LIBRARY, libplugin::F_S_STRICT) }

#endif

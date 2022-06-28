#ifndef LIBPLUGIN_FACTORY_H
#define LIBPLUGIN_FACTORY_H

#include <memory>
#include <unordered_map>

#include "library.hpp"

namespace libplugin {

typedef std::unordered_map<std::string, std::shared_ptr<library>>  library_map;

class factory {
public:
    factory(std::string, int);
    status open(std::string, int, int);
    void close(std::string);
    void close();
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

#define FACTORY_VIEW_SYMBOL(FACTORY, SYMBOL_NAME, LIB_NAME, POLICY) \
    REINTERPRET_CAST_SYMBOL(&SYMBOL_NAME, FACTORY->view(MACRO_TO_STRING(SYMBOL_NAME), LIB_NAME, POLICY))

#endif

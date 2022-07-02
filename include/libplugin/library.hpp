#ifndef LIBPLUGIN_LIBRARY_H
#define LIBPLUGIN_LIBRARY_H

#include <mutex>
#include <dlfcn.h>
#include <any>

#include "status.hpp"

// #ifdef __cplusplus
// extern "C" {
// #endif

namespace libplugin {

class library {
public:
    library();
    library(const char*, int);
    ~library();
    status open(const char*, int);
    void close();
    void* view(const char*);
    void* handle();
protected:
    void* ptr;
    std::string name;
    std::mutex mtx;
};

std::string cxx_demangle(const char*);

}

#define TO_CHARS(x) #x

#define TO_STRING(x) std::string(TO_CHARS(x))

#define IDENTITY(LIB, ARG) \
    std::string(LIB) + "@" + TO_STRING(ARG) + "@" + libplugin::cxx_demangle(typeid(ARG).name())

#define SYMBOL_TYPE(ARG) IDENTITY("", ARG)

#define ANY_CAST_OBJ(SYMBOL, ANY_OBJ) \
    std::any_cast<decltype(SYMBOL)>(ANY_OBJ)

#define LIBRARY_SYMBOL(LIBRARY, SYMBOL) \
    LIBRARY->view(TO_CHARS(SYMBOL))

#define REINTERPRET_CAST_OBJ(SYMBOL, OBJ) \
    reinterpret_cast<decltype(SYMBOL)>(OBJ)

#define LIB_VIEW_SYMBOL(LIBRARY, SYMBOL) \
    REINTERPRET_CAST_OBJ(&SYMBOL, LIBRARY->view(TO_CHARS(SYMBOL)))

#define LIB_SYMBOL_PAIR(LIBRARY, SYMBOL) \
    { SYMBOL_TYPE(SYMBOL), LIB_VIEW_SYMBOL(LIBRARY, SYMBOL) }

// #ifdef __cplusplus
// }
// #endif

#endif
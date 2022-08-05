#ifndef LIBPLUGIN_LIBRARY_H
#define LIBPLUGIN_LIBRARY_H

#include <dlfcn.h>
#include <mutex>
#include <any>

#include "status.hpp"

// #ifdef __cplusplus
// extern "C" {
// #endif

namespace libplugin {

class library {
public:
    ~library();
    library();
    library(const char*, int);
    status open(const char*, int);
    void close();
    void* view(const char*);
    void* handle();
    std::string path();
protected:
    void* ptr;
    std::string name;
    std::mutex mtx;
};

std::string cxx_demangle(const char*);

}

#define TO_CHARS(x) #x

#define TO_STRING(x) std::string(TO_CHARS(x))

#define L_IDENTITY(LIB, ARG) \
    TO_STRING(ARG) + "#" + libplugin::cxx_demangle(typeid(ARG).name()) + "@" + std::string(LIB)

#define N_IDENTITY(ARG) L_IDENTITY("", ARG)

#define ANY_CAST_OBJ(SYMBOL, ANY_OBJ) \
    std::any_cast<decltype(SYMBOL)>(ANY_OBJ)

#define LIB_SYMBOL(LIBRARY, SYMBOL) \
    LIBRARY->view(TO_CHARS(SYMBOL))

#define R_CAST_OBJ(SYMBOL, OBJ) \
    reinterpret_cast<decltype(SYMBOL)>(OBJ)

#define LIB_VIEW_SYMBOL(LIBRARY, SYMBOL) \
    R_CAST_OBJ(&SYMBOL, LIBRARY->view(TO_CHARS(SYMBOL)))

#define LIB_SYMBOL_PAIR(LIBRARY, SYMBOL) \
    { N_IDENTITY(SYMBOL), LIB_VIEW_SYMBOL(LIBRARY, SYMBOL) }

// #ifdef __cplusplus
// }
// #endif

#endif
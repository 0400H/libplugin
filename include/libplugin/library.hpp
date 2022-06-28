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
private:
    void* ptr;
    std::mutex mtx;
};

std::string cxx_demangle(const char*);

}

#define MACRO_TO_CHARS(x) #x

#define MACRO_TO_STRING(x) std::string(MACRO_TO_CHARS(x))

#define GEN_RAW_TYPE_NAME(LIB, ARG) \
    std::string(LIB) + "@" + MACRO_TO_STRING(ARG) + "@" + libplugin::cxx_demangle(typeid(ARG).name())

#define GEN_ARG_TYPE_NAME(ARG) GEN_RAW_TYPE_NAME("", ARG)

#define ANY_CAST_SYMBOL(SYMBOL_NAME, ANY_OBJ) \
    std::any_cast<decltype(SYMBOL_NAME)>(ANY_OBJ)

#define REINTERPRET_CAST_SYMBOL(SYMBOL_NAME, OBJ) \
    reinterpret_cast<decltype(SYMBOL_NAME)>(OBJ)

#define LIB_VIEW_SYMBOL(LIBRARY, SYMBOL_NAME) \
    REINTERPRET_CAST_SYMBOL(&SYMBOL_NAME, LIBRARY->view(MACRO_TO_CHARS(SYMBOL_NAME)))

#define GEN_LIB_SYMBOL_PAIR(LIBRARY, SYMBOL_NAME) \
    { GEN_ARG_TYPE_NAME(SYMBOL_NAME), LIB_VIEW_SYMBOL(LIBRARY, SYMBOL_NAME) }

// #ifdef __cplusplus
// }
// #endif

#endif
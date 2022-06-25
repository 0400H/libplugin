
#include <core/logger/logger.hpp>

#ifdef __linux__
    // linux
#elif defined(_WIN64) || defined(_WIN32)
    #define dlclose(args) FreeLibrary(args)
    #define dlclose_func_name "FreeLibrary"
    #define dlopen(path, arg2) LoadLibrary(path)
    #define dlopen_func_name "LoadLibrary"
    #define dlsym(handle, func) GetProcAddress(handle, func)
    #define dlsym_func_name "GetProcAddress"
    #define dlerror() GetLastError()
#elif defined(__APPLE__)
    // apple
#elif defined(__ANDROID__)
    // android
#elif defined(__unix__) // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
    #error "Unknown compiler"
#endif

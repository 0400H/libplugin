#ifndef library_H
#define library_H

#include <mutex>
#include <dlfcn.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace plugin {

class library {
public:
    library();
    library(const char*, int);
    ~library();
    void open(const char*, int);
    void close();
    void* get_func(const char*);
    void* get_handle();
private:
    void* handle;
    std::mutex mutex;
};

// #define GetLibFunc(lib, return_type, name, ...) \
//     reinterpret_cast<return_type (*)(__VA_ARGS__)>(lib.get_func(name))

}

#ifdef __cplusplus
}
#endif

#endif
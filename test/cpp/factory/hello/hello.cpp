#include "hello.hpp"
// #include "plugin.h"

#ifdef __cplusplus
extern "C" {
#endif

std::string LIBRARY_API hello() {
    return "hello";
};

std::string LIBRARY_API plugin() {
    return "hello plugin";
};

#ifdef __cplusplus
}
#endif

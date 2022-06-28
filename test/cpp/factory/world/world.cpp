#include "world.hpp"
// #include "plugin.h"

#ifdef __cplusplus
extern "C" {
#endif

std::string LIBRARY_API world() {
    return "world";
};

std::string LIBRARY_API plugin() {
    return "world plugin";
};

#ifdef __cplusplus
}
#endif

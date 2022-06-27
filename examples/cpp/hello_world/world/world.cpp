#include "world.hpp"
// #include "plugin.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

void LIBRARY_API world() {
    printf("world!\n");
};

void LIBRARY_API plugin() {
    printf("world plugin!\n");
};

#ifdef __cplusplus
}
#endif

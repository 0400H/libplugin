#include "hello.hpp"
// #include "plugin.h"
#include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

void LIBRARY_API hello() {
    printf("hello!\n");
};

void LIBRARY_API plugin() {
    printf("hello plugin!\n");
};

#ifdef __cplusplus
}
#endif

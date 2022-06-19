#include "libplugin/api.hpp"

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

// LIBPLUGIN_API
std::string LIBRARY_API test_lib(std::string);

#ifdef __cplusplus
}
#endif
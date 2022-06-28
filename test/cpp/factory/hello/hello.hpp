#include "libplugin/api.hpp"

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

std::string LIBRARY_API hello();

std::string LIBRARY_API plugin();

#ifdef __cplusplus
}
#endif

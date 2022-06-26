#include "libplugin/container.hpp"

namespace libplugin {
    // https://blog.csdn.net/only_1/article/details/80285212
    // https://blog.csdn.net/CaspianSea/article/details/46616819

    long container::operator[](const std::string & func_string) {
        return this->funcs[func_string];
    };

}
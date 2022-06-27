#include "libplugin/container.hpp"

namespace libplugin {
    // https://blog.csdn.net/only_1/article/details/80285212
    // https://blog.csdn.net/CaspianSea/article/details/46616819

    void container::insert(std::string type, std::any arg) {
        this->map[type] = arg;
    };

    std::any container::get(std::string type) {
        return this->map.at(type);
    };

}
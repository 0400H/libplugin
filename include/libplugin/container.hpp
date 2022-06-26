#ifndef LIBPLUGIN_CONTAINER_H
#define LIBPLUGIN_CONTAINER_H

#include <unordered_map>
#include <functional>

namespace libplugin {

class container {
public:
    long operator[](const std::string &);
private:
    std::unordered_map<std::string, long> funcs;
};

}

#endif
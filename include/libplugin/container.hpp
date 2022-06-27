#ifndef LIBPLUGIN_CONTAINER_H
#define LIBPLUGIN_CONTAINER_H

#include <unordered_map>
#include <any>

#define type_name(type_arg) \
    typeid(type_arg).name()

#define type_cast(type_arg, any_arg) \
    std::any_cast<decltype(type_arg)>(any_arg)

namespace libplugin {

    class container {
    public:
        void insert(std::string, std::any);
        std::any get(std::string);
    private:
        std::unordered_map<std::string, std::any> map;
    };

}

#endif
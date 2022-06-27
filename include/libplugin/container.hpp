#ifndef LIBPLUGIN_CONTAINER_H
#define LIBPLUGIN_CONTAINER_H

#include <unordered_map>
#include <any>

#define to_string(x) std::string(#x)

#define type_name(type_arg) \
    to_string(type_arg) + "@" + typeid(type_arg).name()

#define type_cast(type_arg, any_arg) \
    std::any_cast<decltype(type_arg)>(any_arg)

#define insert_type_object(container, type_arg) \
    container->insert(typename(type_arg), &type_arg)

#define get_type_object(container, type_arg) \
    type_cast(&type_arg, container->get(typename(type_arg)))

namespace libplugin {

    class container {
    public:
        void insert(std::string, std::any);
        template<typename T>
        void insert(std::string, std::any);
        std::any get(std::string);
    private:
        std::unordered_map<std::string, std::any> map;
    };

}

#endif
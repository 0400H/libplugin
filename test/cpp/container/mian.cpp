#include "cpp/utils.hpp"
#include "libplugin/container.hpp"

#include <string>
#include <typeinfo>
#include <unordered_map>
#include <any>

namespace space {

int value = -1;

std::string func(std::string arg) {
    spdlog::info(arg);
    return arg;
};

};

TEST_CASE("container") {
    spdlog::set_level(spdlog::level::debug);

    auto container = std::make_shared<libplugin::container>();
    auto type_value = type_name(space::value);
    auto type_func = type_name(space::func);
    container->insert(type_value, &space::value);
    container->insert(type_func, &space::func);
    auto value = type_cast(&space::value, container->get(type_value));
    auto func = type_cast(&space::func, container->get(type_func));

    space::value = 1;
    *value = -1;

    CHECK( ((*value) == space::value) );
    CHECK( ((*func)(type_func) == space::func(type_func)) );
}

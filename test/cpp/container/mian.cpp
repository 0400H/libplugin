#include "cpp/utils.hpp"
#include "libplugin/container.hpp"

#include <string>
#include <typeinfo>
#include <unordered_map>
#include <any>

namespace space {

int value = -1;

class object {
public:
    object(std::string value) {
        this->name = value;
    };
    std::string name;
};

std::shared_ptr<object> create_object(std::string value) {
    return std::make_shared<object>(value);
};

};

TEST_CASE("container") {
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");

    auto container = std::make_shared<libplugin::container>();

    auto type_value = type_name(space::value);
    auto type_object = type_name(space::create_object);
    spdlog::info(fmt::format("{} {}", type_value, type_object));

    container->insert(type_value, &space::value);;
    container->insert(type_object, &space::create_object);

    auto value = type_cast(&space::value, container->get(type_value));
    auto object = type_cast(&space::create_object, container->get(type_object));

    space::value = 1;
    *value = -1;

    CHECK( ((*value) == space::value) );
    CHECK( ((*object)(type_object)->name == space::create_object(type_object)->name) );
}

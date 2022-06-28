#include "cpp/utils.hpp"
#include "libplugin/registry.hpp"

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

TEST_CASE("registry") {
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");

    auto registry = std::make_shared<libplugin::registry>();

    auto type_value = type_name(space::value);
    auto type_object = type_name(space::create_object);
    spdlog::info("{} {}", type_value, type_object);

    registry->register_arg(type_value, &space::value, 0);
    registry->register_arg(type_object, &space::create_object, 1);

    auto value = any_type_cast(&space::value, registry->view(type_value));
    auto object = get_any_type_object(registry, space::create_object);

    space::value = 1;
    *value = -1;

    CHECK( ((*value) == space::value) );
    CHECK( ((*object)(type_object)->name == space::create_object(type_object)->name) );
}

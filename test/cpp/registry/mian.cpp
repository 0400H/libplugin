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
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");

    auto registry = std::make_shared<libplugin::registry>();

    auto symbol_value = SYMBOL_TYPE(space::value);
    auto symbol_object = SYMBOL_TYPE(space::create_object);
    spdlog::info("{} {}", symbol_value, symbol_object);

    registry->register_symbol(symbol_value, &space::value, 0);
    registry->register_symbol(symbol_object, &space::create_object, 1);

    auto value = ANY_CAST(&space::value, registry->view(symbol_value));
    auto object = REGISTRY_VIEW_SYMBOL(registry, space::create_object);

    space::value = 1;
    *value = -1;

    CHECK( ((*value) == space::value) );
    CHECK( ((*object)(symbol_object)->name == space::create_object(symbol_object)->name) );
}

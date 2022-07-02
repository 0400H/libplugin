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

    // Automatic symbol type derivation using macro SYMBOL_TYPE
    auto symbol_value = SYMBOL_TYPE(space::value);
    auto symbol_object = SYMBOL_TYPE(space::create_object);
    spdlog::info("symbol type -> {}, {}", symbol_value, symbol_object);

    // register symbol to registry by useing different override policies
    registry->register_symbol(symbol_value, &space::value, 0);
    registry->register_symbol(symbol_value, &space::value, 1);
    registry->register_symbol(symbol_value, &space::value, 2);

    // use macro REGISTRY_REGISTER_SYMBOL to register symbol
    REGISTRY_REGISTER_SYMBOL(registry, space::create_object, 1);
    registry->register_symbol(symbol_object, &space::create_object, 0);

    // use two macro to get symbol from registry
    auto value = ANY_CAST_OBJ(&space::value, registry->view(symbol_value));
    auto object = REGISTRY_VIEW_SYMBOL(registry, space::create_object);

    space::value = 1;
    *value = -1;

    CHECK( ((*value) == space::value) );
    CHECK( ((*object)(symbol_object)->name == space::create_object(symbol_object)->name) );
}

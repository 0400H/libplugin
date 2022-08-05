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
    auto registry = std::make_shared<libplugin::registry>();

    // Automatic symbol type derivation using macro N_IDENTITY
    auto symbol_value = N_IDENTITY(space::value);
    auto symbol_object = N_IDENTITY(space::create_object);
    spdlog::debug("symbol type -> {}, {}", symbol_value, symbol_object);

    // using different override policies to register symbol
    REGISTRY_REGISTER_SYMBOL(registry, space::value, libplugin::R_OVERRIDE);
    REGISTRY_REGISTER_SYMBOL(registry, space::value, libplugin::R_FORBID);
    REGISTRY_REGISTER_SYMBOL(registry, space::value, libplugin::R_STRICT);

    // using macro REGISTRY_REGISTER_SYMBOL to register symbol
    REGISTRY_REGISTER_SYMBOL(registry, space::create_object, libplugin::R_FORBID);
    registry->register_symbol(symbol_object, &space::create_object, libplugin::R_OVERRIDE);

    // using two macro to get symbol from registry
    auto value = REGISTRY_VIEW_N_SYMBOL(registry, space::value);
    auto object = ANY_CAST_OBJ(&space::create_object, registry->view(symbol_object));

    space::value = 1;
    *value = -1;

    CHECK( ((*value) == space::value) );
    CHECK( ((*object)(symbol_object)->name == space::create_object(symbol_object)->name) );
}

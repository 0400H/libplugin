#include "cpp/utils.hpp"
#include "libplugin/library.hpp"
#include "test_lib/test_lib.hpp"

TEST_CASE("library") {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");

    auto lib = std::make_shared<libplugin::library>("test_lib/libtest_lib.so", RTLD_LAZY);
    auto func = reinterpret_cast<decltype(&test_lib)>(lib->view("test_lib"));
    // auto func = reinterpret_cast<std::string (*)(std::string)>(lib->view("test_lib"));

    CHECK( (func("test_lib") == "test_lib") );
}

#include "cpp/utils.hpp"
#include "libplugin/library.hpp"
#include "test_lib/test_lib.hpp"

TEST_CASE("library") {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info(fmt::format("start to test {}.", "doctest, fmt and spdlog"));

    auto lib = std::make_shared<libplugin::library>("test_lib/libtest_lib.so", RTLD_LAZY);
    auto func = reinterpret_cast<std::string (*)(std::string)>(lib->get_func("test_lib"));

    CHECK( (func("test_lib") == "test_lib") );
}

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>
#include <spdlog/spdlog.h>
#include <fmt/format.h>
#include <fmt/printf.h>

#include "libplugin/library.hpp"
// #include "test_lib/test_lib.hpp"

TEST_CASE("library") {
    spdlog::info(fmt::format("start to test {}.", "doctest, fmt and spdlog"));

    class plugin::library lib("test_lib/libtest_lib.so", RTLD_LAZY);
    auto func = reinterpret_cast<std::string (*)(std::string)>(lib.get_func("test_lib"));

    CHECK( (func("test_lib") == "test_lib") );
}

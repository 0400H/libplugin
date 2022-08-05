#include "cpp/utils.hpp"
#include "libplugin/library.hpp"
#include "test_lib/test_lib.hpp"

TEST_CASE("library") {
    auto lib = std::make_shared<libplugin::library>("test_lib/libtest_lib.so", RTLD_LAZY);
    auto func = LIB_VIEW_SYMBOL(lib, test_func);
    // auto func = reinterpret_cast<decltype(&test_func)>(lib->view("test_func"));
    // auto func = reinterpret_cast<std::string (*)(std::string)>(lib->view("test_func"));

    CHECK( (func("test") == "test") );
}

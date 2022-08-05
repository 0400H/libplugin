# Libplugin

## What's the libplugin

Libplugin is a framework which provide ability to get symbols from shared library.

## Why use the libplugin

It provide some different abstraction layers to achieve different degrees of flexibility to meet various usage scenarios.

The core of libplugin is implemented by CPP currently and provides multi language high-level interfaces to simplify use.

## Multi programming language support

- CPP

    The core of implementation.

- C (TODO)

    The bridge of modern programming language.

- Rust (TODO)

    Planned to use rust instead of CPP implementation as the core due to the memory security.

- Python (TODO)

    Python is easy to use, isn't it?

## Multi operation system support

- Linux

    Best Practices.

- Windows

    Need to do, maybe.

- MacOS

    Need to do, maybe.

## Abstraction layers

From low to high degree of abstraction.

### libplugin::library

It responsible for controlling the life cycle of a shared library and providing symbol acquisition interfaces.

```c++
#include "test_lib/test_lib.hpp"

auto lib = std::make_shared<libplugin::library>("test_lib/libtest_lib.so", RTLD_LAZY);
auto func = LIB_VIEW_SYMBOL(lib, test_lib);
auto str = func("hello_world");
```

### libplugin::factory

As a library factory, it provides management and symbol acquisition policies for multiple Libraries.

```c++
auto hello_path = "hello/libtesthello.so";
auto world_path = "world/libtestworld.so";

// using factory to open library with policy
auto factory = std::make_shared<libplugin::factory>(hello_path, RTLD_LAZY);
factory->open(world_path, RTLD_LAZY, libplugin::F_L_STRICT);

// using macro FACTORY_VIEW_SYMBOL to find func with policy
auto hello_func = FACTORY_VIEW_SYMBOL(factory, hello, hello_path, libplugin::F_S_STRICT);
auto world_func = FACTORY_VIEW_SYMBOL(factory, world, world_path, libplugin::F_S_STRICT);
auto plugin_func = FACTORY_VIEW_SYMBOL(factory, plugin, world_path, libplugin::F_S_FUZZY);
```

### libplugin::registry

Register all the required symbols to the registry for easy retrieval and use.

```c++
auto registry = std::make_shared<libplugin::registry>();

// Automatic symbol type derivation using macro N_IDENTITY
auto symbol_value = N_IDENTITY(space::value);
auto symbol_object = N_IDENTITY(space::create_object);
spdlog::info("symbol type -> {}, {}", symbol_value, symbol_object);

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
```

### libplugin::plugin

Provide templates for workflow and resource management of customized plugin to increase user perception transparency and provide additional capabilities.


Customed plugin

```c++
class my_plugin : public libplugin::plugin_base {
public:
    my_plugin();
    ~my_plugin();
    libplugin::status init() override;
    void release() override;
    void unload_all();
private:
    std::shared_ptr<libplugin::factory> factory = nullptr;
};

libplugin::status my_plugin::init() {
    // create func registry
    this->registry = std::make_shared<libplugin::registry>();

    // create library factory
    this->factory = std::make_shared<libplugin::factory>();

    // load libs to factory
    auto hello_path = "hello/libhello.so";
    auto world_path = "world/libworld.so";
    this->factory->open(hello_path, RTLD_LAZY, libplugin::F_L_DEFAULT);
    this->factory->open(world_path, RTLD_LAZY, libplugin::F_L_OVERRIDE);

    // get symbols table
    libplugin::symbol_table hello_world_symbol = {
        FACTORY_N_SYMBOL_PAIR(this->factory, hello, hello_path, libplugin::F_S_STRICT),
        FACTORY_N_SYMBOL_PAIR(this->factory, world, hello_path, libplugin::F_S_FUZZY),
        FACTORY_L_SYMBOL_PAIR(this->factory, plugin, hello_path),
        FACTORY_L_SYMBOL_PAIR(this->factory, plugin, world_path),
    };

    // register symbols to registry
    auto status = this->registry->register_symbols(hello_world_symbol, libplugin::R_OVERRIDE);

    // print status
    libplugin::parse_status(status);
    return status;
};
```

Use customed plugin

```c++
int main() {
    // create my_plugin instance
    auto plugin_impl = std::make_shared<my_plugin>();

    // get symbol registry from instance
    auto registry = plugin_impl->view_all();

    // print symbols in registry
    for (auto& pair : registry->view_all()) {
        spdlog::info("registered symbol -> {}.", pair.first);
    };

    // get symbol from registry
    auto hello_path = "hello/libhello.so";
    auto world_path = "world/libworld.so";
    // Fuzzy search symbol by using macro REGISTRY_VIEW_N_SYMBOL
    auto hello_func = *REGISTRY_VIEW_N_SYMBOL(registry, hello);
    auto world_func = *REGISTRY_VIEW_N_SYMBOL(registry, world);
    // search raw symbol by using macro REGISTRY_VIEW_L_SYMBOL
    auto hello_plugin_func = *REGISTRY_VIEW_L_SYMBOL(registry, plugin, hello_path);
    auto world_plugin_func = *REGISTRY_VIEW_L_SYMBOL(registry, plugin, world_path);

    // run func
    hello_func();
    world_func();
    hello_plugin_func();
    world_plugin_func();

    // unload symbol if u want
    registry->unload_symbol(N_IDENTITY(hello));
    registry->unload_symbol(L_IDENTITY(hello_path, plugin));
    registry->unload_symbol("plugin#void ()@world/libworld.so");
    return 0;
}
```

## How to contribute?

- Docker development environment (TODO)

    Recommend `ubuntu 18.04` `ubuntu 20.04`

- Workflow

    - Firstly

        - Start && Fork as downstream.
        - Git clone the downstream (your private fork).
        - Setup your development environment.

    - Others

        - Create a issue about your idea in the upstream repo (the root repo).
        - Git rebase to upstream.
        - Coding.
        - Git commit.
        - Create pull request as upstream (your repo) to the downstream (the root repo).
        - Comminicate && Review.
        - Merge to the downstream.

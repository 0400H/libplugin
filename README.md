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
auto lib = std::make_shared<libplugin::library>("test_lib/libtest_lib.so", RTLD_LAZY);

auto func = reinterpret_cast<decltype(&test_lib)>(lib->view("test_lib"));
// auto func = reinterpret_cast<std::string (*)(std::string)>(lib->view("test_lib"));
```

### libplugin::factory

As a library factory, it provides management and symbol acquisition policies for multiple Libraries.

```c++
auto hello_path = "hello/libtesthello.so";
auto world_path = "world/libtestworld.so";

auto factory = std::make_shared<libplugin::factory>(hello_path, RTLD_LAZY);
factory->open(world_path, RTLD_LAZY, 2);

// Automatic symbol type derivation using macro FACTORY_VIEW_SYMBOL
auto hello_func = FACTORY_VIEW_SYMBOL(factory, hello, hello_path, 0);
auto world_func = FACTORY_VIEW_SYMBOL(factory, world, world_path, 0);
auto plugin_func = FACTORY_VIEW_SYMBOL(factory, plugin, world_path, 1);
```

### libplugin::registry

Register all the required symbols to the registry for easy retrieval and use.

```c++
auto registry = std::make_shared<libplugin::registry>();

// Automatic symbol type derivation using macro SYMBOL_TYPE
auto symbol_value = SYMBOL_TYPE(space::value);
auto symbol_object = SYMBOL_TYPE(space::create_object);

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
```

### libplugin::plugin

Provide templates for workflow and resource management of customized plugin to increase user perception transparency and provide additional capabilities.


Custom plugin

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
    this->factory->open("hello/libhello.so", RTLD_LAZY, 0);
    this->factory->open("world/libworld.so", RTLD_LAZY, 1);

    // get symbols map
    libplugin::symbol_table hello_world_symbol = {
        FACTORY_SYMBOL_PAIR(this->factory, hello, hello_path, 0),
        FACTORY_SYMBOL_PAIR(this->factory, world, hello_path, 1),
        FACTORY_IDENTITY_PAIR(this->factory, plugin, hello_path),
        FACTORY_IDENTITY_PAIR(this->factory, plugin, world_path),
    };

    // register symbols to registry
    auto status = this->registry->register_symbols(hello_world_symbol, 0);

    // print status
    libplugin::parse_status(status);
    return status;
};
```

Use customed plugin

```c++
int main() {
    spdlog::set_level(spdlog::level::trace);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e %l %t] %v");

    // create my_plugin instance
    auto plugin_impl = std::make_shared<my_plugin>();

    // get symbol registry from instance
    auto registry = plugin_impl->view_all();

    // print symbols of registry
    for (auto& pair : registry->view_all()) {
        spdlog::info("registered symbol -> {}.", pair.first);
    };

    // get symbol from registry
    // Fuzzy search symbol by using macro REGISTRY_VIEW_SYMBOL
    auto hello_func = *REGISTRY_VIEW_SYMBOL(registry, hello);
    auto world_func = *REGISTRY_VIEW_SYMBOL(registry, world);
    // Factory mode search symbol by using two macro
    auto hello_plugin_identity = IDENTITY("hello/libhello.so", plugin);
    auto hello_plugin_func = *ANY_CAST_OBJ(&plugin, registry->view(hello_plugin_identity));
    auto world_plugin_func = *REGISTRY_VIEW_RAW_SYMBOL(registry, plugin, "world/libworld.so");

    // run func
    hello_func();
    world_func();
    hello_plugin_func();
    world_plugin_func();

    // unload symbol if u want
    registry->unload_symbol(SYMBOL_TYPE(hello));
    registry->unload_symbol("world/libworld.so@plugin@void ()");
    registry->unload_symbol(hello_plugin_identity);
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

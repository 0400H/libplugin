#ifndef LIBPLUGIN_FACTORY_H
#define LIBPLUGIN_FACTORY_H

#include <any>
#include <memory>
#include <unordered_map>

#include "library.hpp"

namespace libplugin {

typedef std::unordered_map<std::string, std::shared_ptr<library>>  library_map;

class factory {
public:
    factory(std::string);
    status open(std::string, int);
    status close(std::string);
    status close();
    status as_default(std::string);
    std::any view(std::string, std::string);
    std::any view(std::string);
    std::vector<std::any> view(std::vector<std::string>, std::string, int);
    std::vector<std::any> view(std::vector<std::string>);
protected:
    std::string default_lib;
    library_map bucket;
};

}

#endif
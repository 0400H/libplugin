#ifndef LIBPLUGIN_STATUS_H
#define LIBPLUGIN_STATUS_H

#include <string>
#include <vector>

namespace libplugin {

// https://github.com/arzzen/all-exit-error-codes/blob/master/programming-languages/c/errors.md

enum status {
    S_Success             = 0,
    S_Failed              = 1 << 0,
    S_UnInitialized       = 1 << 1,
    S_InvalidValue        = 1 << 2,
    S_MemAllocFailed      = 1 << 3,
    S_UnImplError         = 1 << 4,
    S_UnKownError         = 1 << 5,
};

std::vector<std::string> parse_status(status code);

std::vector<std::string> print_status(status code);

}

#endif
#include <spdlog/spdlog.h>

#include "libplugin/status.hpp"
#include "libplugin/logger.hpp"

namespace libplugin {

std::vector<std::string> parse_status(status code) {
    std::vector<std::string> status_msg;
    if (code == S_Success) {
        status_msg.emplace_back("Success");
    } else {
        int level = 0;
        while (level < 6) {
            if (code & (1 << level)) {
                switch (level) {
                    case 0:
                        status_msg.emplace_back("Failed");
                    case 1:
                        status_msg.emplace_back("UnInitialized");
                    case 2:
                        status_msg.emplace_back("InvalidValue");
                    case 3:
                        status_msg.emplace_back("MemAllocFailed");
                    case 4:
                        status_msg.emplace_back("UnImplError");
                    case 5:
                        status_msg.emplace_back("UnKownError");
                    default:
                        break;
                };
            };
            level++;
        };
    };
    return status_msg;
};

std::vector<std::string> print_status(status code) {
    auto status_msg = parse_status(code);
    for (auto& msg : status_msg) {
        spdlog::info(msg);
    };
};

}

#include "libplugin/status.hpp"
#include "core/utils.hpp"

namespace libplugin {

std::vector<std::string> parse_status(status code) {
    spdlog::trace("parse_status {0:b}", code);
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
                        break;
                    case 1:
                        status_msg.emplace_back("UnInitialized");
                        break;
                    case 2:
                        status_msg.emplace_back("InvalidValue");
                        break;
                    case 3:
                        status_msg.emplace_back("MemAllocFailed");
                        break;
                    case 4:
                        status_msg.emplace_back("UnImplError");
                        break;
                    case 5:
                        status_msg.emplace_back("UnKownError");
                        break;
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
    return status_msg;
};

}

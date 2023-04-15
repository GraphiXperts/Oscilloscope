#ifndef _THREAD_CONFIGURATION_HPP_
#define _THREAD_CONFIGURATION_HPP_

#include <ECL/impl/thread.hpp>

namespace th {

namespace ThreadConfigs {
enum {
    Default,

    Ordinary,
    Processing,

    Count
};
}

namespace ProcessType {
    enum {
        Other,
        Processing,
        Idle,
        Render,
        Count
    };
}

void ThreadConfig();

}  // namespace th

#endif
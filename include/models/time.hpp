#ifndef _MODELS_TIME_HPP_
#define _MODELS_TIME_HPP_

#include <cmath>
#include <ctime>

namespace mdl {

////////////////////////////////////////////////////////////////
// \brief Object that used as extendet timestamp
////////////////////////////////////////////////////////////////
using time_t = long double;

////////////////////////////////////////////////////////////////
// \brief Object that contains information about extended time
////////////////////////////////////////////////////////////////
struct tm : public std::tm {
    int tm_millisec;  // Milliseconds. [0-1000]
    int tm_microsec;  // Microseconds. [0-1000]
    int tm_nanosec;   // Nanoseconds.  [0-1000]
};

tm fromStdTm(std::tm t);

tm localtime(time_t t);

time_t mktime(tm t);

const tm NULL_TM = localtime(0);

}  // namespace mdl

#endif // _MODELS_TIME_HPP_
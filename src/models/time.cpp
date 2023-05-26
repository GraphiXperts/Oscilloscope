#include <models/time.hpp>

namespace mdl {

constexpr long double MILLISEC_DUR = 1 / 1000;
constexpr long double MICROSEC_DUR = MILLISEC_DUR / 1000;
constexpr long double NANOSEC_DUR  = MICROSEC_DUR / 1000;

tm fromStdTm(std::tm t) {
    return {t.tm_sec,  t.tm_min,  t.tm_hour, t.tm_mday,  t.tm_mon,
            t.tm_year, t.tm_wday, t.tm_yday, t.tm_isdst, t.tm_gmtoff,
            t.tm_zone, 0,         0,         0};
}

tm localtime(time_t t) {
    std::time_t tt(t);
    tm result        = fromStdTm(*std::localtime(&tt));
    long double time = t - std::floor(t);

    result.tm_millisec = std::floor(time *= 1000);  // milliseconds
    result.tm_microsec = std::floor(time *= 1000);  // microseconds
    result.tm_nanosec  = std::floor(time *= 1000);  // nanoseconds

    return result;
}

time_t mktime(tm t) {
    return t.tm_millisec * MILLISEC_DUR + t.tm_microsec * MICROSEC_DUR +
           t.tm_nanosec * NANOSEC_DUR + std::mktime(&t);
}

}  // namespace mdl
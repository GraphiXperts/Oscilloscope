#include <models/signal_parsers/istream_wrapper.hpp>
#include <models/signal_parsers/txt_parser.hpp>
#include <models/time.hpp>

namespace mdl {

////////////////////////////////////////////////////////////////
/// TxtParser implementation
////////////////////////////////////////////////////////////////

TxtParser::TxtParser() = default;

TxtParser::TxtParser(const TxtParser& other) = default;

TxtParser::TxtParser(TxtParser&& other) = default;

TxtParser::~TxtParser() {}

//----------------------------------------------------------------

TxtParser& TxtParser::operator=(const TxtParser& other) = default;

TxtParser& TxtParser::operator=(TxtParser&& other) = default;

//----------------------------------------------------------------

VResult<Signal> TxtParser::parse(std::istream& input) const {
    istream_wrapper in(input);
    Signal result;

    try {
        size_t channel_count, sample_count;
        in >> channel_count >> sample_count;

        long double frequency;
        in >> frequency;

        long double begin_time;
        {
            tm begin_tm = NULL_TM;

            // Reading the begin date.
            in.ignore('-');
            in >> begin_tm.tm_mday >> begin_tm.tm_mon >> begin_tm.tm_year;
            begin_tm.tm_mon--;
            begin_tm.tm_year -= 1900;
            in.attract('-');

            // Reading the begin time.
            in.ignore(':');
            in >> begin_tm.tm_hour >> begin_tm.tm_min;
            long double sec;
            in >> sec;
            begin_tm.tm_sec      = std::floor(sec);
            begin_tm.tm_millisec = std::floor((sec -= begin_tm.tm_sec) *= 1000);
            begin_tm.tm_microsec = std::floor((sec -= begin_tm.tm_millisec) *= 1000);
            begin_tm.tm_nanosec  = std::floor((sec -= begin_tm.tm_microsec) * 1000);
            in.attract(':');

            begin_time = mktime(begin_tm);
        }

        std::vector<Channel> channels(channel_count);

        std::vector<std::string> channel_names(channel_count);

        // Reading the channels name
        in.delimiter(';');
        for (size_t i = 0; i < channel_count; ++i)
            in >> channel_names[i];

        size_t avg_sample_count = sample_count / channel_count;

        // Reading the channels values
        for (size_t i = 0; i < avg_sample_count; ++i) {
            long double sample_time = begin_time + i / frequency;

            for (size_t j = 0; j < channel_count; ++j) {
                long double sample_value;
                in >> sample_value;
                channels[j].add({sample_value, sample_time});
            }
        }
        in.undelimiter(';');

        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        for (size_t i = 0; i < channel_count; ++i) {
            result.addChannel(std::move(channels[i]));
            result.getChannelWrapperPtr(i)->setName(converter.from_bytes(channel_names[i]));
        }

    } catch (...) {
        return Err("Something went wrong...");
    }

    return Ok(std::move(result));
}

}  // namespace mdl
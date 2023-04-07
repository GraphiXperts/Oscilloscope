#pragma once
#include <string>
#include <fstream>
#include <array>

#include <models/Parsers/Parser.h>
#include <models/Signal.h>

namespace parse {


class TxtParser: public ParserInterface {
public:
    TxtParser() = default;
    models::Signal Parse(std::istream& stream) override;
    ~TxtParser() override = default;

private:
    void read_while_not_comment(std::istream& file, std::string& s);
    models::TimeDate&& parse_date_time(std::string& str, std::istream& file);
    std::array<std::string,3> parse_three_entities(const std::string& str, const char& delimiter);
    void parse_channels_names(std::string& str, models::Signal& signal);
    void parse_frequency(std::istream& file, models::Signal& signal, models::TimeDate start_td);
};

}//namespace


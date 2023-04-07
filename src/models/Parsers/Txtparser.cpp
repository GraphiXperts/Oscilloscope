#include <models/Parsers/Txtparser.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <sstream>
using std::stod;

namespace parse {

void TxtParser::read_while_not_comment(std::istream& file, std::string& s) {

    while (!file.eof()) {
        std::getline(file, s);
        
        if (s[0] != '#')
            return;
    }
    
}

std::array<std::string,3> TxtParser::parse_three_entities(const std::string& str, const char& delimiter) {
    std::array<std::string,3> tokens;
    std::size_t counter = 0;
    std::size_t pos = 0;

    while (pos != std::string::npos) {
        std::size_t end_pos = str.find(delimiter, pos);
        if (end_pos == std::string::npos) {
            tokens[counter++] = str.substr(pos);
            break;
        }
        tokens[counter++] = str.substr(pos, end_pos - pos);
        pos = end_pos + 1;
    }

    return tokens;
}

models::TimeDate&& TxtParser::parse_date_time(std::string& str,  std::istream& file) {
    //date parsing
    auto tokens_date = parse_three_entities(str, '-');
    
    //time parsing
    read_while_not_comment(file, str);
    auto tokens_time = parse_three_entities(str, ':');
    
    models::TimeDate td(
        stod(tokens_time[2]), stod(tokens_time[1]), stod(tokens_time[0]), 
        stoi(tokens_date[0]), stoi(tokens_date[1]), stoi(tokens_date[2]));

    
    return std::move(td);
}

void TxtParser::parse_channels_names(std::string& str, models::Signal& signal) {
    std::vector<std::string> tokens;
    std::string delimiter = ";";
    size_t pos = 0;

    bool flag = false;
    if (str[str.size()-1] != ';')
        flag = true;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        models::Channel chan(str.substr(0, pos));
        signal.add_channel(std::move(chan));
        str.erase(0, pos + delimiter.length());
    }
    
    if (flag) 
        signal.add_channel(std::move(str));
}

void TxtParser::parse_frequency(std::istream& file, models::Signal& signal, models::TimeDate time) {
    models::Bounds bounds;
    bounds.start_time = time;

    double number;
    uint64_t chan_count = signal.get_channel_count();

    std::vector<double> max_values(chan_count, -999999999);
    std::vector<double> min_values(chan_count, 999999999);
    uint64_t chan_index;
    models::TimeValue tv(time, number);

    for (uint64_t i = 0; i < signal.get_reports_count(); ++i) {
        
        chan_index = i % chan_count;
        file >> number;
        
        if (number > max_values[chan_index])
            max_values[chan_index] = number;
        if (number < min_values[chan_index])
            min_values[chan_index] = number;
        
        tv.t = time; tv.v = number;

        signal.get_channels()[chan_index].add_time_value(tv);

        if ((chan_index) == (chan_count - 1))
            time.add_seconds(1.0/signal.get_sampling_frequency());
    }
    bounds.end_time = time;

    for(size_t i = 0; i < chan_count; ++i) {
        bounds.max_value = max_values[i];
        bounds.min_value = min_values[i];
        signal.get_channels()[i].set_bounds(bounds);
    }
    

}

models::Signal TxtParser::Parse(std::istream& file) {
    std::string s;

    uint64_t reports_count, channels_count;
    double sampling_frequency;

    //channel parsing
    read_while_not_comment(file, s);
    channels_count = std::stoull(s); 
     
    //reports parsing
    read_while_not_comment(file,s);
    reports_count = std::stoull(s);
    
    //sampling parsing
    read_while_not_comment(file, s);
    sampling_frequency = std::stod(s);
    models::Signal signal(sampling_frequency, reports_count);
    
    //date-time parsing
    read_while_not_comment(file, s);
    auto date_time = parse_date_time(s, file);
    
    
    //channels name parsing
    read_while_not_comment(file, s);
    parse_channels_names(s, signal);

    //TODO:
    //frequency parsing
    parse_frequency(file, signal, date_time);
    
    return signal;

}
} // namespace parse
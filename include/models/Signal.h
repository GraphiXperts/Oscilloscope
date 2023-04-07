#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

namespace models {
struct TimeDate {
    TimeDate(double sec, double min, double hour, uint32_t day, uint32_t month, uint32_t year): 
            sec(sec), min(min), hour(hour),
            day(day), month(month), year(year) {}

    //FIXME: to timestamp
    TimeDate(double seconds): sec(seconds) {}
    TimeDate(): TimeDate(0) {}

	double sec;		
	double min;		
	double hour;

	uint32_t day;
	uint32_t month;	
	uint32_t year;	

    double to_timestamp();

    std::string to_string();
    std::wstring to_wstring();

    void add_seconds(double delta) {
    this->sec += delta;
    if (this->sec >= 60) {
        this->sec -= 60;
        this->min += 1;
    }
    if (this->min >= 60) {
        this->min -= 60;
        this->hour += 1;
    }
    if (this->hour >= 24) {
        this->hour -= 24;
        this->day += 1;
    }

    if (this->day >= 31) {
        this->day -= 31;
        this->month += 1;
    }
    if (this->month >= 12) {
        this->month -= 12;
        this->year += 1;
    }
}
	
};


struct Bounds {
    TimeDate start_time;
    TimeDate end_time;

    double max_value;
    double min_value;
};

struct TimeValue {
    TimeValue(TimeDate t, double v): t(t), v(v) {}
    TimeDate t;
    double v;
};

class Channel {
    using container = std::vector<TimeValue>;
    using iterator = container::iterator;
public:

    Channel(std::string&& name): name(std::move(name)) {}
    Channel(std::string&& name, container&& freq, Bounds bounds) : 
            name(std::move(name)), frequency(std::move(freq)),bounds(bounds) {}
    Channel(Channel&& other) = default;

    Bounds get_bounds() const {return bounds;}
    void set_bounds(Bounds bounds) {this->bounds = bounds;}
    const std::string& get_name() const {return name;}
    container get_frequency() {return frequency;}
    void add_time_value(TimeValue tv) {frequency.push_back(tv);}

    //FIXME:
    //std::pair<iterator, iterator> get_window(TimeDate start_time, TimeDate end_time);
private:
    Bounds bounds;
    container frequency; 
    std::string name;
};


class Signal{
public:
    Signal() = default;
    Signal(Signal&& signal) = default;
    Signal(double samp_freq, uint64_t reports_count): sampling_frequency(samp_freq), reports_count(reports_count) {}
    
    Signal& operator=(Signal&& signal) = default;
  
    std::vector<Channel>& get_channels() {return channels;}
    void add_channel(Channel&& chan) {channels.emplace_back(std::move(chan));}
    uint64_t get_reports_count() {return reports_count;} // N
    double get_sampling_frequency() {return sampling_frequency;}
    uint64_t get_channel_count() {return channels.size();}

private:
    double sampling_frequency; // частота дискретизации
    uint64_t reports_count;
    std::vector<Channel> channels;
};
}
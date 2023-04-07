#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

namespace models {
struct TimeDate {
    TimeDate(double sec, double min, double hour, uint32_t day, uint32_t month, uint32_t year);

    //FIXME: to timestamp
    TimeDate(double seconds): sec(seconds) {}
    TimeDate(): TimeDate(0) {}

    TimeDate& operator=(TimeDate& td) = default;

	double sec;		
	double min;		
	double hour;

	uint32_t day;
	uint32_t month;	
	uint32_t year;	

    double to_timestamp() const;
    std::string to_string() const;
    std::wstring to_wstring() const;

    //Не прибавляйте больше 60 секунд!!
    void add_seconds(double delta);
	
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
    bool operator<(const TimeValue& other) const;
};

class Channel {
    using container = std::vector<TimeValue>;
public:
    using iterator = container::iterator;
    Channel(std::string&& name): name(std::move(name)) {}
    Channel(std::string&& name, container&& freq, Bounds bounds);
    Channel(Channel&& other) = default;

    Bounds get_bounds() const {return bounds;}
    void set_bounds(Bounds bounds) {this->bounds = bounds;}
    const std::string& get_name() const {return name;}
    container get_frequency() {return frequency;}
    void add_time_value(TimeValue tv) {frequency.push_back(tv);}

    std::pair<iterator, iterator> get_window(TimeDate start_time, TimeDate end_time);
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
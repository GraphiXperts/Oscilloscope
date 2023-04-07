#include <models/Signal.h>
#include <utility> 
#include <algorithm> 
namespace models {

TimeDate::TimeDate(double sec, double min, double hour, uint32_t day, uint32_t month, uint32_t year): 
            sec(sec), min(min), hour(hour),
            day(day), month(month), year(year) {}

//Не прибавляйте больше 60 секунд!!
void TimeDate::add_seconds(double delta) {
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

double TimeDate::to_timestamp() const {
    TimeDate unix_time;
    unix_time.year = 1970;
    unix_time.month = 1;
    unix_time.day = 1;
    unix_time.hour = 0;
    unix_time.min = 0;
    unix_time.sec = 0;

    double timestamp = 0;
    timestamp += (this->year - unix_time.year) * 365 * 24 * 60 * 60;
    timestamp += (this->month - unix_time.month) * 31 * 24 * 60 * 60;
    timestamp += (this->day - unix_time.day) * 24 * 60 * 60;
    timestamp += (this->hour) * 60 * 60;
    timestamp += (this->min) * 60;
    timestamp += (this->sec);

    return timestamp;
}


std::wstring TimeDate::to_wstring() const {
    std::wstring str;
    str += std::to_wstring(this->year);
    str += L"-";
    str += std::to_wstring(this->month);
    str += L"-";
    str += std::to_wstring(this->day);
    str += L" ";
    str += std::to_wstring(this->hour);
    str += L":";
    str += std::to_wstring(this->min);
    str += L":";
    str += std::to_wstring(this->sec);

    return str;
}

std::string TimeDate::to_string() const {
    std::string str;
    str += std::to_string(this->year);
    str += "-";
    str += std::to_string(this->month);
    str += "-";
    str += std::to_string(this->day);
    str += " ";
    str += std::to_string(this->hour);
    str += ":";
    str += std::to_string(this->min);
    str += ":";
    str += std::to_string(this->sec);

    return str;
}

Channel::Channel(std::string&& name, container&& freq, Bounds bounds) : 
            name(std::move(name)), frequency(std::move(freq)),bounds(bounds) {}


auto my_cmp = [](const TimeValue& p1, const TimeValue& p2) {
        if (p1.t.year != p2.t.year)
            return p1.t.year < p2.t.year;
        
        if (p1.t.month != p2.t.month)
            return p1.t.month < p2.t.month;

        if (p1.t.day != p2.t.day)
            return p1.t.day < p2.t.day;

        if (p1.t.hour != p2.t.hour)
            return p1.t.hour < p2.t.hour;

        if (p1.t.min != p2.t.min)
            return p1.t.min < p2.t.min;

        return p1.t.sec < p2.t.sec;
        
    };


bool TimeDate::operator==(const TimeDate& other) const {
    return this->sec == other.sec && this->min == other.min && this->hour == other.hour &&
            this->day == other.day && this->month == other.month && this->year == other.year;
}
bool TimeDate::operator<(const TimeDate& other) const {
    if (this->year != other.year)
            return this->year < other.year;
        
        if (this->month != other.month)
            return this->month < other.month;

        if (this->day != other.day)
            return this->day < other.day;

        if (this->hour != other.hour)
            return this->hour < other.hour;

        if (this->min != other.min)
            return this->min < other.min;

        return this->sec < other.sec;
}

bool TimeDate::operator>(const TimeDate& other) const {
    return other < *this;
}

bool TimeDate::operator<=(const TimeDate& other) const {
    return !(other < *this);
}

bool TimeDate::operator>=(const TimeDate& other) const {
    return !(*this < other);
}

bool TimeDate::operator!=(const TimeDate& other) const {
    return !(*this == other);
}


bool TimeValue::operator< (const TimeValue& p2) const {
    if (t.year != p2.t.year)
            return t.year < p2.t.year;
        
        if (t.month != p2.t.month)
            return t.month < p2.t.month;

        if (t.day != p2.t.day)
            return t.day < p2.t.day;

        if (t.hour != p2.t.hour)
            return t.hour < p2.t.hour;

        if (t.min != p2.t.min)
            return t.min < p2.t.min;

        return t.sec < p2.t.sec;
        
    };

std::pair<Channel::iterator, Channel::iterator> Channel::get_window(TimeDate start_time, TimeDate end_time) {
    
    auto left_it = std::lower_bound(
        this->frequency.begin(), 
        this->frequency.end(),
        TimeValue(start_time, 0.0),
        my_cmp
    );

    auto right_it = std::upper_bound(
        this->frequency.begin(),
        this->frequency.end(),
        TimeValue(end_time, 0.0),
        my_cmp
    );

    return {left_it, right_it};
}
}//namespace models






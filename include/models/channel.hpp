#ifndef _MODELS_CHANNEL_HPP_
#define _MODELS_CHANNEL_HPP_

#include <models/result.hpp>
#include <models/time.hpp>
#include <string>
#include <vector>
#include <memory>

namespace mdl {

typedef long double eval_t;
typedef long double etime_t;

////////////////////////////////////////////////////////////////
// \brief Object that represents a channel sample.
////////////////////////////////////////////////////////////////
struct Sample {
    eval_t value; // value of the sample
    etime_t time; // time of the sample
};

////////////////////////////////////////////////////////////////
// \brief Object that representing a channel range pointer.
////////////////////////////////////////////////////////////////
class Range {
 public:
    using iterator = std::vector<Sample>::const_iterator;

 protected:
    iterator begin_;  // The begin of the range
    iterator end_;    // The end of the range
 public:
    // Default constructor
    Range();
    // Constructor with begin and end
    Range(iterator begin, iterator end);
    // Copy constructor
    Range(const Range& other);
    // Move constructor
    Range(Range&& other);
    // Destructor
    ~Range();

    // Assignment operators

    // Copy assignment operator
    Range& operator=(const Range& other);
    // Move assignment operator
    Range& operator=(Range&& other);

    // Return the begin of the range
    iterator begin() const;
    // Return the end of the range
    iterator end() const;

    // Return size of the range
    size_t size() const;
    // Return true if the range is empty
    bool empty() const;
};

////////////////////////////////////////////////////////////////
// \brief Object that representing a channel.
////////////////////////////////////////////////////////////////
class Channel {
 protected:
    using Container = std::vector<Sample>;

    Container samples_;  // Contain samples of the channel

 public:
    // Default constructor
    Channel();
    // Constructor with copy container
    Channel(const Container& elements);
    // Constructor with move container
    Channel(Container&& elements);
    // Copy constructor
    Channel(const Channel& other);
    // Move constructor
    Channel(Channel&& other);
    // Destructor
    ~Channel();

    // Assignment operators

    // Copy assignment operator
    Channel& operator=(const Channel& other);
    // Move assignment operator
    Channel& operator=(Channel&& other);

    // Methods

    // Get reference to element with index
    Sample& at(size_t index);
    // Get const reference to element with index
    const Sample& at(size_t index) const;
    // Add element to the channel
    void add(const Sample& element);
    // Remove element from the channel
    Result remove(size_t index);
    // Remove all elements from the channel
    void clear();
    // Get size of the channel
    size_t size() const;

    // Get range of the channel
    VResult<Range> range(size_t begin, size_t end) const;

};

////////////////////////////////////////////////////////////////
// \brief Object that contains information about a channel.
////////////////////////////////////////////////////////////////
struct ChannelInfo {
    std::wstring name;    // name of the channel
    std::wstring source;  // source of the channel

    size_t sample_count;  // number of samples in the channel

    etime_t start_time;     // start time of the channel
    etime_t finish_time;    // finish time of the channel
    etime_t duration_time;  // duration of the channel

    etime_t max_frequency;  // maximum frequency
    etime_t min_frequency;  // minimum frequency
    etime_t avg_frequency;  // average frequency
};

// Creates informations about a channel.
ChannelInfo getInfo(const Channel& channel);

////////////////////////////////////////////////////////////////
// \brief Object that used to wrap a channel.
////////////////////////////////////////////////////////////////
class ChannelWrapper {
 protected:
    std::shared_ptr<const Channel> channel_;  // The channel
    ChannelInfo info_;                        // The channel info

 public:
    // Default constructor.
    ChannelWrapper();
    // Constructor that copy channel.
    ChannelWrapper(const Channel& channel);
    // Constructor that move channel.
    ChannelWrapper(Channel&& channel);
    // Copy constructor.
    ChannelWrapper(const ChannelWrapper& other);
    // Move constructor.
    ChannelWrapper(ChannelWrapper&& other);
    // Destructor.
    ~ChannelWrapper();

    // Assignment operator.

    // Copy assignment operator.
    ChannelWrapper& operator=(const ChannelWrapper& other);
    // Move assignment operator.
    ChannelWrapper& operator=(ChannelWrapper&& other);

    // Accessors.

    // Returns const reference to the channel.
    const Channel& channel() const;
    // Sets the channel.
    void setChannel(const Channel& channel);
    // Moves the channel
    void setChannel(Channel&& channel);
    // Returns channel info.
    const ChannelInfo& info() const;

    // Sets the channel name.
    void setName(const std::wstring& name);
    // Sets the channel source.
    void setSource(const std::wstring& source);

    // Returns true if the channel is valid.
    bool valid() const;
};

////////////////////////////////////////////////////////////////
// \brief Object that transforms a time value into a string.
////////////////////////////////////////////////////////////////
class TimeFormatter {
 public:
    // Virtual destructor
    virtual ~TimeFormatter() = 0;

    // Return the time value as a string
    virtual VResult<std::wstring> format(etime_t time) const = 0;
};

}  // namespace mdl

#endif  // _MODELS_CHANNEL_HPP_
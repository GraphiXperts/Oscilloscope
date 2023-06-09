#ifndef _MODELS_CHANNEL_HPP_
#define _MODELS_CHANNEL_HPP_

#include <models/result.hpp>
#include <models/time.hpp>
#include <string>
#include <vector>

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

    std::wstring name_;   // The name of the channel
    std::wstring source_;   // The name of the channel
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

    // Get name of the channel
    const std::wstring& name() const;
    // Set name of the channel
    void setName(const std::wstring& name);

    // Get source of the channel
    const std::wstring& source() const;
    // Set source of the channel
    void setSource(const std::wstring& source);

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
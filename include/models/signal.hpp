#ifndef _MODELS_SIGNAL_HPP_
#define _MODELS_SIGNAL_HPP_

#include <map>
#include <memory>
#include <models/channel.hpp>
#include <models/result.hpp>
#include <set>
#include <vector>

namespace mdl {

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

    // Returns true if the channel is valid.
    bool valid() const;
};

////////////////////////////////////////////////////////////////
// \brief Object that contains information about a signal.
////////////////////////////////////////////////////////////////
struct SignalInfo {
    std::wstring name;    // name of the signal
    std::wstring source;  // source of the signal

    size_t channel_count;  // number of channels
    size_t sample_count;   // number of samples in the signal

    etime_t start_time;     // start time of the signal
    etime_t finish_time;    // finish time of the signal
    etime_t duration_time;  // duration of the signal

    etime_t max_frequency;  // maximum frequency
    etime_t min_frequency;  // minimum frequency
    etime_t avg_frequency;  // average frequency
    
};

////////////////////////////////////////////////////////////////
// \brief Object representing a signal.
////////////////////////////////////////////////////////////////
class Signal {
 protected:
    std::vector<ChannelWrapper> channels_;  // The channels
    SignalInfo info_;                       // The signal info

    // Updates signal info.
    void update_info();

 public:
    // Default constructor.
    Signal();
    // Copy constructor.
    Signal(const Signal& other);
    // Move constructor.
    Signal(Signal&& other);
    // Destructor.
    ~Signal();

    // Assignment operator.

    // Copy assignment operator.
    Signal& operator=(const Signal& other);
    // Move assignment operator.
    Signal& operator=(Signal&& other);

    // Accessors.

    // Returns const reference to channel.
    const Channel& at(size_t index) const;
    // Returns const reference to channel info.
    const ChannelInfo& getChannelInfo(size_t index) const;
    // Returns const reference to channel wrapper.
    const ChannelWrapper& getChannelWrapper(size_t index) const;

    // Sets channel by copy.
    void setChannel(size_t index, const Channel& channel);
    // Sets channel by move.
    void setChannel(size_t index, Channel&& channel);
    // Sets channel wrapper by copy.
    void setChannelWrapper(size_t index, const ChannelWrapper& channel);
    // Sets channel wrapper by move.
    void setChannelWrapper(size_t index, ChannelWrapper&& channel);

    // Adds channel by copy.
    void addChannel(const Channel& channel);
    // Adds channel by move.
    void addChannel(Channel&& channel);
    // Adds channel wrapper by copy.
    void addChannelWrapper(const ChannelWrapper& channel);
    // Adds channel wrapper by move.
    void addChannelWrapper(ChannelWrapper&& channel);

    // Removes channel by index.
    void removeChannel(size_t index);
    // Removes all channels.
    void clear();

    // Get the number of channels.
    size_t size() const;
    // Get the number of samples.
    size_t sampleCount() const;
    // Get name of signal.
    const std::wstring& name() const;
    // Set name of signal.
    void setName(const std::wstring& name);
    // Get source of signal.
    const std::wstring& source() const;
    // Set source of signal.
    void setSource(const std::wstring& source);
    // Get signal info.
    const SignalInfo& info() const;

    // Returns true if the signal is empty.
    bool empty() const;
};

}  // namespace mdl

#endif  // _MODELS_SIGNAL_HPP_
#include <models/channel.hpp>

namespace mdl {

////////////////////////////////////////////////////////////////
/// Range implementation
////////////////////////////////////////////////////////////////

Range::Range() = default;

Range::Range(iterator begin, iterator end) : begin_(begin), end_(end) {}

Range::Range(const Range &other) = default;

Range::Range(Range &&other) = default;

Range::~Range() = default;

//----------------------------------------------------------------

Range &Range::operator=(const Range &other) = default;

Range &Range::operator=(Range &&other) = default;

//----------------------------------------------------------------

Range::iterator Range::begin() const { return begin_; }

Range::iterator Range::end() const { return end_; }

size_t Range::size() const { return std::distance(begin_, end_); }

bool Range::empty() const { return begin_ == end_; }

////////////////////////////////////////////////////////////////
/// Channel implementation
////////////////////////////////////////////////////////////////

Channel::Channel() = default;

Channel::Channel(const Container &elements) : samples_(elements) {}

Channel::Channel(Container &&elements) : samples_(std::move(elements)) {}

Channel::Channel(const Channel &other) = default;

Channel::Channel(Channel &&other) = default;

Channel::~Channel() = default;

//----------------------------------------------------------------

Channel &Channel::operator=(const Channel &other) = default;

Channel &Channel::operator=(Channel &&other) = default;

//----------------------------------------------------------------

Sample& Channel::at(size_t index) {
    return samples_.at(index);
}

const Sample& Channel::at(size_t index) const {
    return samples_.at(index);
}

void Channel::add(const Sample &element) { samples_.push_back(element); }

Result Channel::remove(size_t index) {
    if (index >= samples_.size())
        return Err("Invalid index of element to remove");
    samples_.erase(samples_.begin() + index);
}

void Channel::clear() { samples_.clear(); }

size_t Channel::size() const { return samples_.size(); }

VResult<Range> Channel::range(size_t begin, size_t end) const {
    if (begin >= size() || end > size() || end < begin)
        return Err("Invalid range");
    return Ok(Range(samples_.begin() + begin, samples_.begin() + end));
}

////////////////////////////////////////////////////////////////
/// ChannelInfo implementation
////////////////////////////////////////////////////////////////

ChannelInfo getInfo(const Channel& channel) {
    ChannelInfo info;
    info.sample_count = channel.size();

    info.start_time    = INFINITY;
    info.finish_time   = -INFINITY;
    info.duration_time = 0;

    info.max_frequency = -INFINITY;
    info.min_frequency = INFINITY;
    info.avg_frequency = 0;

    Range range    = *channel.range(0, channel.size());
    size_t counter = 0;

    for (auto i = range.begin(); i != range.end(); i++) {
		info.start_time = std::min(info.start_time, i->time);
		info.finish_time = std::max(info.finish_time, i->time);
		info.duration_time = info.finish_time - info.start_time;

        if (i != range.begin()) {
            auto p       = i - 1;
            etime_t dist = 1.0 / (i->time - p->time);

            info.max_frequency = std::max(info.max_frequency, dist);
            info.min_frequency = std::min(info.min_frequency, dist);
            info.avg_frequency =
                    (info.avg_frequency * counter + dist) / (counter + 1);
			
        	counter++;
        }
    }

    return info;
}

////////////////////////////////////////////////////////////////
/// ChannelWrapper implementation
////////////////////////////////////////////////////////////////

ChannelWrapper::ChannelWrapper() = default;

ChannelWrapper::ChannelWrapper(const Channel& channel)
    : channel_(new Channel(channel)), info_(getInfo(channel)) {}

ChannelWrapper::ChannelWrapper(Channel&& channel)
    : channel_(new Channel(std::move(channel))), info_(getInfo(*channel_)) {}

ChannelWrapper::ChannelWrapper(const ChannelWrapper& other) = default;

ChannelWrapper::ChannelWrapper(ChannelWrapper&& other) = default;

ChannelWrapper::~ChannelWrapper() = default;

//----------------------------------------------------------------

ChannelWrapper& ChannelWrapper::operator=(const ChannelWrapper& other) =
    default;

ChannelWrapper& ChannelWrapper::operator=(ChannelWrapper&& other) = default;

//----------------------------------------------------------------

const Channel& ChannelWrapper::channel() const { return *channel_; }

void ChannelWrapper::setChannel(const Channel& channel) {
    channel_.reset(new Channel(channel));
    info_ = getInfo(channel);
}

void ChannelWrapper::setChannel(Channel&& channel) {
    channel_.reset(new Channel(std::move(channel)));
    info_ = getInfo(channel);
}

void ChannelWrapper::setName(const std::wstring& name) {
    info_.name = name;
}

void ChannelWrapper::setSource(const std::wstring& source) {
    info_.source = source;
}

const ChannelInfo& ChannelWrapper::info() const { return info_; }

bool ChannelWrapper::valid() const { return channel_ != nullptr; }

}  // namespace mdl
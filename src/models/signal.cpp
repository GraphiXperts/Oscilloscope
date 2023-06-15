#include <models/signal.hpp>

namespace mdl {

////////////////////////////////////////////////////////////////
/// Signal implementation
////////////////////////////////////////////////////////////////

void Signal::update_info() {
    info_.channel_count = channels_.size();
    info_.sample_count  = 0;

    info_.start_time    = INFINITY;
    info_.finish_time   = -INFINITY;
    info_.duration_time = 0;

    info_.max_frequency = -INFINITY;
    info_.min_frequency = INFINITY;
    info_.avg_frequency = 0;

    uint64_t counter = 0;

    for (size_t i = 0; i < info_.channel_count; i++) {
        const ChannelInfo& c_info = channels_[i].info();

        info_.sample_count += c_info.sample_count;
        info_.start_time  = std::min(info_.start_time, c_info.start_time);
        info_.finish_time = std::max(info_.finish_time, c_info.finish_time);

        info_.max_frequency =
            std::max(info_.max_frequency, c_info.max_frequency);
        info_.min_frequency =
            std::min(info_.min_frequency, c_info.min_frequency);

        if (counter == 0)
            info_.avg_frequency = c_info.avg_frequency;
        else
            info_.avg_frequency =
                (info_.avg_frequency * counter + c_info.avg_frequency * c_info.sample_count) /
                (counter + c_info.sample_count);

        counter += c_info.sample_count;
    }
}

Signal::Signal() = default;

Signal::Signal(const Signal& other) = default;

Signal::Signal(Signal&& other) = default;

Signal::~Signal() = default;

//----------------------------------------------------------------

Signal& Signal::operator=(const Signal& other) = default;

Signal& Signal::operator=(Signal&& other) = default;

//----------------------------------------------------------------

const Channel& Signal::at(size_t index) const {
    return channels_.at(index).channel();
}

const ChannelInfo& Signal::getChannelInfo(size_t index) const {
    return channels_.at(index).info();
}

const ChannelWrapper& Signal::getChannelWrapper(size_t index) const {
    return channels_.at(index);
}

ChannelWrapper* Signal::getChannelWrapperPtr(size_t index) {
    return &channels_.at(index);
}

void Signal::setChannel(size_t index, const Channel& channel) {
    channels_.at(index).setChannel(channel);
    update_info();
}

void Signal::setChannel(size_t index, Channel&& channel) {
    channels_.at(index).setChannel(std::move(channel));
    update_info();
}

void Signal::setChannelWrapper(size_t index, const ChannelWrapper& channel) {
    channels_.at(index) = channel;
    update_info();
}

void Signal::setChannelWrapper(size_t index, ChannelWrapper&& channel) {
    channels_.at(index) = std::move(channel);
    update_info();
}

void Signal::addChannel(const Channel& channel) {
    channels_.emplace_back(channel);
    update_info();
}

void Signal::addChannel(Channel&& channel) {
    channels_.emplace_back(std::move(channel));
    update_info();
}

void Signal::addChannelWrapper(const ChannelWrapper& channel) {
    channels_.emplace_back(channel);
    update_info();
}

void Signal::addChannelWrapper(ChannelWrapper&& channel) {
    channels_.emplace_back(std::move(channel));
    update_info();
}

void Signal::removeChannel(size_t index) {
    channels_.erase(channels_.begin() + index);
    update_info();
}

void Signal::clear() {
    channels_.clear();
    update_info();
}

size_t Signal::size() const { return channels_.size(); }

size_t Signal::sampleCount() const { return info_.sample_count; }

const std::wstring& Signal::name() const { return info_.name; }

void Signal::setName(const std::wstring& name) { info_.name = name; }

const std::wstring& Signal::source() const { return info_.source; }

void Signal::setSource(const std::wstring& source) { info_.source = source; }

const SignalInfo& Signal::info() const { return info_; }

bool Signal::empty() const { return info_.channel_count == 0; }

}  // namespace mdl
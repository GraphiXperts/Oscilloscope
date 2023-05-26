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

const std::wstring &Channel::name() const { return name_; }

void Channel::setName(const std::wstring &name) { name_ = name; }

}  // namespace mdl
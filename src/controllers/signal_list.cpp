#include <controllers/signal_list.hpp>

namespace ctrl {

////////////////////////////////////////////////////////////////
/// SignalWrapper implementation
////////////////////////////////////////////////////////////////

SignalWrapper::SignalWrapper(const mdl::Signal& signal) : signal_(signal) {}

SignalWrapper::SignalWrapper(mdl::Signal&& signal)
    : signal_(std::move(signal)) {}

SignalWrapper::~SignalWrapper() {}

void SignalWrapper::notify(SignalMessage mes) {}

void SignalWrapper::send(SignalMessage mes) {
    for (auto& el : ptrs_) el->notify(mes);
}

SignalPointer SignalWrapper::getPtr() {
    ptrs_.push_back(nullptr);
    SignalPointer ptr(this, std::prev(ptrs_.end()));
    return ptr;
}

////////////////////////////////////////////////////////////////
/// SignalPointer implementation
////////////////////////////////////////////////////////////////

void SignalPointer::detach() {
    if (signal_ != nullptr) {
        signal_->ptrs_.erase(pos_);
        signal_ = nullptr;
    }
}

//----------------------------------------------------------------

SignalPointer::SignalPointer() : signal_(nullptr) {}

SignalPointer::SignalPointer(SignalWrapper* signal, Pos pos)
    : signal_(signal), pos_(pos) {}

SignalPointer::SignalPointer(const SignalPointer& other)
    : signal_(other.signal_) {
    if (signal_ != nullptr) {
        signal_->ptrs_.push_back(this);
        pos_ = std::prev(signal_->ptrs_.end());
    }
}

SignalPointer::SignalPointer(SignalPointer&& other)
    : signal_(other.signal_), pos_(other.pos_) {
    if (signal_ != nullptr) {
        other.signal_ = nullptr;
        *pos_         = this;
    }
}

SignalPointer::~SignalPointer() { detach(); }

//----------------------------------------------------------------

SignalPointer& SignalPointer::operator=(const SignalPointer& other) {
    detach();

    signal_ = other.signal_;
    signal_->ptrs_.push_back(this);
    pos_ = std::prev(signal_->ptrs_.end());

    return *this;
}

SignalPointer& SignalPointer::operator=(SignalPointer&& other) {
    detach();

    if (signal_ != nullptr) {
        signal_ = other.signal_;
        pos_    = other.pos_;

        other.signal_ = nullptr;
        *pos_         = this;
    }

    return *this;
}

SignalPointer& SignalPointer::operator=(SignalWrapper* other) {
    detach();

    if (other != nullptr) {
        *this = std::move(other->getPtr());
    }
}

//----------------------------------------------------------------

void SignalPointer::notify(SignalMessage message) {}

void SignalPointer::send(SignalMessage message) { signal_->send(message); }

mdl::Signal& SignalPointer::getSignal() { return signal_->signal_; }

bool SignalPointer::valid() const {
    return signal_ != nullptr;
}

////////////////////////////////////////////////////////////////
/// FSignalPointer implementation
////////////////////////////////////////////////////////////////

FSignalPointer::FSignalPointer(SignalWrapper* signal, Pos pos)
    : Base(signal, pos) {}

FSignalPointer::FSignalPointer(const Self& other) = default;

FSignalPointer::FSignalPointer(Self&& other) = default;

FSignalPointer::~FSignalPointer() = default;

//----------------------------------------------------------------

FSignalPointer& FSignalPointer::operator=(const Self& other) = default;

FSignalPointer& FSignalPointer::operator=(Self&& other) = default;

//----------------------------------------------------------------

void FSignalPointer::notify(SignalMessage mes) { function_(mes); }

void FSignalPointer::setFunction(FunctionObject&& function) {
    function_ = std::move(function);
}

////////////////////////////////////////////////////////////////
/// SignalList implementation
////////////////////////////////////////////////////////////////

SignalList::SignalList() = default;

//----------------------------------------------------------------

SignalList::~SignalList() = default;

SignalList* SignalList::getInstance() {
    if (instance_ == nullptr) instance_ = new SignalList();
    return instance_;
}

SignalList::Pos SignalList::add(const mdl::Signal& signal) {
    signals_.push_back(signal);
    return std::prev(signals_.end());
}

SignalList::Pos SignalList::add(mdl::Signal&& signal) {
    signals_.emplace_back(std::move(signal));
    return std::prev(signals_.end());
}

void SignalList::remove(Pos pos) { signals_.erase(pos); }

SignalList::Pos SignalList::at(size_t index) {
    return std::next(signals_.begin(), index);
}

size_t SignalList::size() const { return signals_.size(); }

}  // namespace ctrl
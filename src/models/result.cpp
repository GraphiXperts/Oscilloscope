#include <models/result.hpp>

namespace mdl {

////////////////////////////////////////////////////////////////
/// Result implementation
////////////////////////////////////////////////////////////////

Result::Result() = default;

Result::Result(const std::string& message) : message_(message) {}

Result::Result(std::string&& message) : message_(std::move(message)) {}

Result::Result(const Result& other) = default;

Result::Result(Result&& other) = default;

Result::~Result() = default;

Result& Result::operator=(const Result& other) = default;

Result& Result::operator=(Result&& other) = default;

const std::string& Result::m() const { return message_; }

Result::operator bool() const { return message_.empty(); }

Result Ok() { return Result(); }

Result Err(const std::string& message) { return Result(message); }

Result Err(std::string&& message) { return Result(std::move(message)); }

} // namespace mdl
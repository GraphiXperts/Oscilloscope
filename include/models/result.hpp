#ifndef _MODELS_RESULT_HPP_
#define _MODELS_RESULT_HPP_

#include <string>
#include <type_traits>

namespace mdl {

////////////////////////////////////////////////////////////////
// \brief Object representing the result of any process.
////////////////////////////////////////////////////////////////
class Result {
 protected:
    std::string message_;

 public:
    // Default constructor.
    Result();
    // Constructor with a copy error message.
    Result(const std::string& message);
    // Constructor with a move error message.
    Result(std::string&& message);
    // Copy constructor.
    Result(const Result& other);
    // Move constructor.
    Result(Result&& other);
    // Destructor.
    ~Result();

    // Assignment operator.

    // Copy assignment operator.
    Result& operator=(const Result& other);
    // Move assignment operator.
    Result& operator=(Result&& other);

    // Accessors.
    const std::string& m() const;

    operator bool() const;
};

Result Ok();

Result Err(const std::string& message);

Result Err(std::string&& message);

////////////////////////////////////////////////////////////////
// \brief Object representing the result of a process with
// return value.
////////////////////////////////////////////////////////////////
template <typename Type,
          typename std::enable_if<!std::is_reference<Type>::value, bool>::type =
              true>
class VResult : public Result {
 protected:
    using Self = VResult<Type>;
    using Base = Result;

    Type value_;

 public:
    // Default constructor.
    VResult() : value_(nullptr) {}
    // Constructor with a value.
    template <typename T>
    VResult(T&& value) : value_(std::forward<T>(value)) {}
    // Constructor with a copy error message.
    VResult(const std::string& message) : Base(message) {}
    // Constructor with a move error message.
    VResult(std::string&& message) : Base(std::move(message)) {}
    // Copy constructor.
    VResult(const VResult& other) = default;
    // Move constructor.
    VResult(VResult&& other) = default;
    // Constructor from Result.
    VResult(const Result& other) : Base(other) {}
    // Constructor from Result.
    VResult(Result&& other) : Base(std::move(other)) {}
    // Destructor.
    ~VResult() {}

    Type* operator->() { return &value_; }
    const Type* operator->() const { return &value_; }

    Type& operator*() { return value_; }
    const Type& operator*() const { return value_; }

    operator Result() {
		return Result(message_);
    }
};

template <typename Type>
inline VResult<Type> Ok(const Type& value) {
    return VResult<Type>(value);
}

template <typename Type>
inline VResult<Type> Ok(Type&& value) {
    return VResult<Type>(std::move(value));
}

}  // namespace mdl

#endif
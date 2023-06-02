#ifndef _MODELS_ISTREAM_WRAPPER_HPP_
#define _MODELS_ISTREAM_WRAPPER_HPP_

#include <istream>
#include <set>

namespace mdl {

////////////////////////////////////////////////////////////////
// \brief Class used as input stream wrapper.
////////////////////////////////////////////////////////////////
class istream_wrapper {
 public:
    std::istream& input_;           // input stream
    bool ignore_chars_[256];        // characters to ignore
    bool line_comment_chars_[256];  // characters of comments
    bool delimiter_chars_[256];     // delimiter characters

    void ignore_spaces();

    // Constructor from istream.
    istream_wrapper(std::istream& is);
    // Destructor
    ~istream_wrapper();

    template <typename Type>
    friend istream_wrapper& operator>>(istream_wrapper& is, Type& value) {
        is.ignore_spaces();
        is.input_ >> value;
        return is;
    }

    friend istream_wrapper& operator>>(istream_wrapper& is,
                                       std::string& value) {
        is.ignore_spaces();
        while (true) {
            char c = is.input_.peek();
            if (!is.delimiter_chars_[c]) {
                value.push_back(is.input_.get());
            } else {
                break;
            }
        }
    }

    // Add ignoring character.
    void ignore(char c);
    // Add ignoring characters.
    void ignore(std::initializer_list<char> chars);

    // Remove ignoring character.
    void attract(char c);
    // Remove ignoring characters.
    void attract(std::initializer_list<char> chars);

    // Add line comment character.
    void comment(char c);
    // Add line comment characters.
    void comment(std::initializer_list<char> chars);

    // Remove line comment character.
    void uncomment(char c);
    // Remove line comment characters.
    void uncomment(std::initializer_list<char> chars);

    // Add delimiter character.
    void delimiter(char c);
    // Add delimiter characters.
    void delimiter(std::initializer_list<char> chars);

    // Remove delimiter character.
    void undelimiter(char c);
    // Remove delimiter characters.
    void undelimiter(std::initializer_list<char> chars);
};

}  // namespace mdl

#endif  // _MODELS_ISTREAM_WRAPPER_HPP_
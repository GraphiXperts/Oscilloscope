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
    std::istream& input_; // input stream
    std::set<char> ignore_chars_; // characters to ignore
    std::set<char> line_comment_chars_; // characters of comments

    void ignore_spaces();

public:
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

    // Add ignoring character.
    void ignore(char c);

    // Remove ignoring character.
    void attract(char c);
};


} // namespace mdl

#endif // _MODELS_ISTREAM_WRAPPER_HPP_
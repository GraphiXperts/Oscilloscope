#include <models/signal_parsers/istream_wrapper.hpp>
#include <limits>

namespace mdl {

////////////////////////////////////////////////////////////////
/// ISteamWrapper implementation
////////////////////////////////////////////////////////////////

istream_wrapper::istream_wrapper(std::istream& is) : input_(is) {
    for (int i = 0; i < 256; ++i) {
        ignore_chars_[i] = false;
        line_comment_chars_[i] = false;
        delimiter_chars_[i] = false;
    }
    ignore({' ', '\r', '\t', '\n'});
    comment({'#'});
    delimiter({' ', '\t', '\r', '\n'});
}

istream_wrapper::~istream_wrapper() = default;

void istream_wrapper::ignore_spaces() {
    while (true) {
        char c = input_.peek();
        if (ignore_chars_[c])
            input_.get();
        else if (line_comment_chars_[c])
            input_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        else
            break;
    }
}

void istream_wrapper::ignore(char c) { 
    ignore_chars_[c] = true;    
}

void istream_wrapper::ignore(std::initializer_list<char> chars) {
    for (char c : chars)
        ignore(c);
}

void istream_wrapper::attract(char c) {
    ignore_chars_[c] = false;
}

void istream_wrapper::attract(std::initializer_list<char> chars) {
    for (char c : chars)
        attract(c);
}

void istream_wrapper::comment(char c) {
    line_comment_chars_[c] = true;
}

void istream_wrapper::comment(std::initializer_list<char> chars) {
    for (char c : chars)
        comment(c);
}

void istream_wrapper::delimiter(char c) {
    delimiter_chars_[c] = true;
}

void istream_wrapper::delimiter(std::initializer_list<char> chars) {
    for (char c : chars)
        delimiter(c);
}

void istream_wrapper::undelimiter(char c) {
    delimiter_chars_[c] = false;
}

void istream_wrapper::undelimiter(std::initializer_list<char> chars) {
    for (char c : chars)
        undelimiter(c);
}

}  // namespace mdl
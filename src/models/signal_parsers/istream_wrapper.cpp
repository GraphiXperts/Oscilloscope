#include <models/signal_parsers/istream_wrapper.hpp>
#include <limits>

namespace mdl {

////////////////////////////////////////////////////////////////
/// ISteamWrapper implementation
////////////////////////////////////////////////////////////////

istream_wrapper::istream_wrapper(std::istream& is) : input_(is) {
    ignore_chars_.insert({' ', '\r', '\t', '\n'});
    line_comment_chars_.insert({'#'});
}

istream_wrapper::~istream_wrapper() = default;

void istream_wrapper::ignore_spaces() {
    while (true) {
        char c = input_.peek();
        if (ignore_chars_.find(c) != ignore_chars_.end())
            input_.get();
        else if (line_comment_chars_.find(c) != line_comment_chars_.end())
            input_.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        else
            break;
    }
}

void istream_wrapper::ignore(char c) { ignore_chars_.insert(c); }

void istream_wrapper::attract(char c) { ignore_chars_.erase(c); }

}  // namespace mdl
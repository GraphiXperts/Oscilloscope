#ifndef _MODELS_PARSER_HPP_
#define _MODELS_PARSER_HPP_

#include <istream>
#include <map>
#include <models/result.hpp>
#include <models/signal.hpp>
#include <string>

namespace mdl {

////////////////////////////////////////////////////////////////
// \brief Base class for all signal parsers.
////////////////////////////////////////////////////////////////
class ParserBase {
 public:
    // Virtual destructor.
    virtual ~ParserBase() = 0;

    // Parse a signal from a stream.
    virtual VResult<Signal> parse(std::istream& in) const = 0;
};

////////////////////////////////////////////////////////////////
// \brief Class used to parse files containing signals.
////////////////////////////////////////////////////////////////
class FileParser {
 protected:
    std::map<const std::string, std::shared_ptr<ParserBase>>
        parsers_;  // Map from file extension to parser.

 public:
    // Default constructor.
    FileParser();
    // Copy constructor.
    FileParser(const FileParser& other);
    // Move constructor.
    FileParser(FileParser&& other);
    // Destructor.
    ~FileParser();

    // Assignment operators.

    // Copy assignment operator.
    FileParser& operator=(const FileParser& other);
    // Move assignment operator.
    FileParser& operator=(FileParser&& other);

    // Parse a signal from a path to file.
    VResult<Signal> parse(const std::string& path) const;

    // Add parser for a file extension.
    Result addParser(const std::string& ext, std::shared_ptr<ParserBase> parser);
    // Remove parser for a file extension.
    Result removeParser(const std::string& ext);
    // Get count of parsers.
    size_t parserCount() const;

};

}  // namespace mdl

#endif  // _MODELS_PARSER_HPP_
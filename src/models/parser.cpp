#include <fstream>
#include <models/parser.hpp>
#include <iostream>
#include <sstream>
#include <codecvt>
#include <locale>

namespace mdl {

////////////////////////////////////////////////////////////////
/// FileParser implementation.
////////////////////////////////////////////////////////////////

FileParser::FileParser() = default;

FileParser::FileParser(const FileParser &other) = default;

FileParser::FileParser(FileParser &&other) = default;

FileParser::~FileParser() = default;

//----------------------------------------------------------------

FileParser &FileParser::operator=(const FileParser &other) = default;

FileParser &FileParser::operator=(FileParser &&other) = default;

//----------------------------------------------------------------

VResult<Signal> FileParser::parse(const std::string &file_path) const {
    std::istringstream input_stream(file_path);
    input_stream.ignore(file_path.size(), '.');

    std::string extension;
    input_stream >> extension;

    if (parsers_.find(extension) == parsers_.end())
        return Err("Unknown file extension");

    std::fstream input_file(file_path, std::ios::in);
    if (!input_file.is_open()) return Err("Could not open file");

    VResult<Signal> result = parsers_.at(extension)->parse(input_file);

    if (result) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        for(int i = 0; i < result->size(); i++)
            result->getChannelWrapperPtr(i)->setSource(converter.from_bytes(std::string("Получен из " + file_path)));
    }

    return result;
}

Result FileParser::addParser(const std::string &extension,
                             std::shared_ptr<ParserBase> parser) {
    if (parsers_.find(extension) != parsers_.end())
        return Err("File extension already registered");

    parsers_.emplace(std::make_pair(extension, parser));
    return Ok();
}

Result FileParser::removeParser(const std::string &extension) {
    if (parsers_.find(extension) == parsers_.end())
        return Err("File extension not registered");

    parsers_.erase(extension);
    return Ok();
}

size_t FileParser::parserCount() const { return parsers_.size(); }

}  // namespace mdl
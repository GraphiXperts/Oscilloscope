#include <models/Parsers/Parser.h>
#include <models/Parsers/Txtparser.h>
#include <algorithm>
#include <fstream>
#include <istream>
namespace parse {

ParserInterface::~ParserInterface() {}

FileParser::FileParser() {
    parsers.insert(std::make_pair("txt", new TxtParser()));
}

models::Signal&& FileParser::Parse(const std::string& path) {
    std::string extension;

    for (auto i = path.rbegin(); *i != '.'; i++)
        extension.push_back(*i);
    std::reverse(extension.begin(), extension.end());
    
    if (parsers.find(extension) == parsers.end())
        throw FileError();
    
    std::ifstream input(path);
    return std::move(parsers[extension]->Parse(input));
}

}
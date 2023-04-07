#pragma once
#include <models/Signal.h>
#include <istream>
#include <map>
namespace parse {


class ParserInterface {
    public:
        virtual ~ParserInterface();

        virtual models::Signal Parse(std::istream& stream) = 0;
    };



class FileParser {
    public:
        FileParser();
        models::Signal&& Parse(const std::string& path);
    private:
        std::map<std::string, ParserInterface*> parsers;

};


struct FileError{};
}



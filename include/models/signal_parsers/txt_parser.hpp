#ifndef _MODELS_TXT_PARSER_HPP_
#define _MODELS_TXT_PARSER_HPP_

#include <models/parser.hpp>
#include <set>
#include <locale>
#include <codecvt>

namespace mdl {

////////////////////////////////////////////////////////////////
// \brief Class used to parse txt files.
////////////////////////////////////////////////////////////////
class TxtParser : public ParserBase {
 public:
    // Default constructor.
    TxtParser();
    // Copy constructor.
    TxtParser(const TxtParser&);
    // Move constructor.
    TxtParser(TxtParser&&);
    // Destructor.
    ~TxtParser() override;

    // Assignment operator.
    
    // Copy assignment operator.
    TxtParser& operator=(const TxtParser&);
    // Move assignment operator.
    TxtParser& operator=(TxtParser&&);

    // Parse the model.
    VResult<Signal> parse(std::istream& input) const override;

};

}

#endif // _MODELS_TXT_PARSER_HPP_
#include <controllers/use_cases.hpp>
#include <models/parser.hpp>
#include <models/signal_parsers/txt_parser.hpp>

namespace ctrl {

mdl::FileParser f_parser;
ctrl::SignalList* signal_list;

void init() {
    f_parser.addParser("txt", std::make_shared<mdl::TxtParser>());

    signal_list = SignalList::getInstance();
}

mdl::VResult<SignalPointer> addSignalFromFile(const std::string& filename) {
    auto result = f_parser.parse(filename);
    
    if (result)
        return mdl::Ok(signal_list->add(*result)->getPtr());
    else
        return mdl::Err(result.m());
}

} // namespace ctrl
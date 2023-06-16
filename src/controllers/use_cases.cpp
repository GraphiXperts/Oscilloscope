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

mdl::VResult<SignalPointer> getSignal() {
    if (signal_list->size() == 0) {
        return mdl::Err("No signals in list");
    }
    return mdl::Ok(signal_list->at(0)->getPtr());
}

mdl::Result addChannel(mdl::ChannelWrapper channel) {
    return mdl::Err("Not implemented");
}

mdl::Result clearChannels() {
    return mdl::Err("Not implemented");
}

} // namespace ctrl
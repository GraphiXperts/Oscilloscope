#ifndef _CONTROLLERS_USE_CASES_HPP_
#define _CONTROLLERS_USE_CASES_HPP_

#include <controllers/signal_list.hpp>

namespace ctrl {

void init();

mdl::VResult<SignalPointer> addSignalFromFile(const std::string &filename);

mdl::VResult<SignalPointer> getSignal();

mdl::Result addChannel(mdl::ChannelWrapper channel);

mdl::Result clearChannels();

} // namespace ctrl

#endif // _CONTROLLERS_USE_CASES_HPP_
#ifndef _CONTROLLERS_MODELING_HPP_
#define _CONTROLLERS_MODELING_HPP_
#include <models/channel.hpp>
#include <memory>
#include <controllers/signal_list.hpp>

namespace ctrl {

class Modeling {
    static void delayedSingleImpulse(ctrl::SignalPointer signal_pointer, const long long N, const long long time, const long long n) {
    
        // channel.setSource(L"Задержанный единичный импульс");
        // channel.setName(L"MODEL_1_");
        // for (long long i = 0; i < N; i++) {
        //     mdl::Sample sample;
        //     sample.time = i;
        //     sample.value = (i == n) ? 1 : 0;
        //     channel.add(sample);
        // } 
    }
};

} // namespace ctrl
#endif  // _CONTROLLERS_MODELING_HPP_
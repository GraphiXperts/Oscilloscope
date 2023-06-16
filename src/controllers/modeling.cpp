#include <controllers/modeling.hpp>
#include <models/channel.hpp>
#include <controllers/use_cases.hpp>
#include <cmath>
#include <iostream>

namespace ctrl {

void Modeling::delayedSingleImpulse(mdl::time_t start_time, const uint64_t N,  const double freq, const uint64_t n, const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;
    channel_wrapper.setSource(L"Задержанный единичный импульс n_0 = " + std::to_wstring(n)); 
    channel_wrapper.setName(L"MODEL_1_" + std::to_wstring(j)); 
    
    for (int i = 0; i < N; i++) {
        mdl::Sample sample;
        
        sample.time = time;
        time += 1/freq;
        sample.value = (i == n) ? 1 : 0;
        channel.add(sample);
    }
    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper); //FIXME: крашнет т.к не имплементировано
}


void Modeling::delayedSingleHop(mdl::time_t start_time, const uint64_t N,  const double freq, const uint64_t n, const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;

    channel_wrapper.setSource(L"Задержанный единичный скачок n_0 = " + std::to_wstring(n));
    channel_wrapper.setName(L"MODEL_2_" + std::to_wstring(j));
    
    for (uint64_t i = 0; i < n; ++i) {
        mdl::Sample sample;
        sample.time = time;
        time += 1/freq;
        sample.value = 0;
        channel.add(sample);
    }

    for (uint64_t i = n; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        time += 1/freq;
        sample.value = 1;
        channel.add(sample);
    }

    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper); //FIXME: крашнет т.к не имплементировано
}

void Modeling::sampledDecreasingExponent(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;

    channel_wrapper.setSource(L"Дискретизированная убывающая экспонента a = " + std::to_wstring(a)); 
    channel_wrapper.setName(L"MODEL_3_" + std::to_wstring(j));

    for (uint64_t i = 0; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        time += 1/freq;
        sample.value = std::pow(a, i);
        channel.add(sample);
    }

    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper); //FIXME: крашнет т.к не имплементировано
}

void Modeling::sampledSineWave(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double circFreq, const double initPhase, const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;


    channel_wrapper.setSource(L"Дискретизированная синусоида"); 
    channel_wrapper.setName(L"MODEL_4_" + std::to_wstring(j));


    for (uint64_t i = 0; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        time += 1/freq;
        sample.value = a * std::sin(i * circFreq + initPhase);
        channel.add(sample);
    }

    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper);
}

void Modeling::meander(mdl::time_t start_time, const uint64_t N,  const double freq, const uint32_t L, const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;


    channel_wrapper.setSource(L"Меандр"); 
    channel_wrapper.setName(L"MODEL_5_" + std::to_wstring(j));

    for (uint64_t i = 0; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        time += 1/freq;
        sample.value = (i % L < L/2) ? 1 : -1;
        channel.add(sample);
    }

    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper);
}

void Modeling::saw(mdl::time_t start_time, const uint64_t N,  const double freq, const uint32_t L, const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;


    channel_wrapper.setSource(L"Пила"); 
    channel_wrapper.setName(L"MODEL_6_" + std::to_wstring(j));

    for (uint64_t i = 0; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        time += 1/freq;
        sample.value = (i % L) / L;
        channel.add(sample);
    }

    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper);
}

void Modeling::exponentialEnvelope(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double tau, const double f, const double phi, const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;


    channel_wrapper.setSource(L"Экспонинцеальная огибающая"); 
    channel_wrapper.setName(L"MODEL_7_" + std::to_wstring(j));

    for (uint64_t i = 0; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        time += 1/freq;
        double t = i / freq;
        sample.value = a * std::exp(-t / tau) * std::cos(2 * M_PI * f * t + phi);
        channel.add(sample);
    }

    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper);
}

void Modeling::balanceEnvelope(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double f0, const double fn, const double phi, const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel ;
    mdl::time_t time = start_time;


    channel_wrapper.setSource(L"Балансная огибающая"); 
    channel_wrapper.setName(L"MODEL_8_" + std::to_wstring(j));

    for (uint64_t i = 0; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        time += 1/freq;
        double t = i / freq;
        sample.value = a * std::cos(2 * M_PI * f0 * t) * std::cos(2 * M_PI * fn * t + phi);
        channel.add(sample);
    }
    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper);
}

void Modeling::tonalEnvelope(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double f0, const double fn, const double phi, const double m,  const uint64_t j) {
    mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;


    channel_wrapper.setSource(L"Тональная огибающая"); 
    channel_wrapper.setName(L"MODEL_9_" + std::to_wstring(j));

    for (uint64_t i = 0; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        double t = i / freq;
        time += 1/freq;
        sample.value = a * (1 + m * std::cos(2 * M_PI * f0 * t) * std::cos(2 * M_PI * fn * t + phi));
        channel.add(sample);
    }

    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper);
}

void Modeling::LFM(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double f0, const double fk, const double phi0, const uint64_t j) {
     mdl::ChannelWrapper channel_wrapper;
    mdl::Channel channel;
    mdl::time_t time = start_time;


    channel_wrapper.setSource(L"Тональная огибающая"); 
    channel_wrapper.setName(L"MODEL_10_" + std::to_wstring(j));

    double totalTime = N / freq;
    for (uint64_t i = 0; i < N; ++i) {
        mdl::Sample sample;
        sample.time = time;
        double t = i / freq;
        time += 1/freq;
        sample.value =a * std::cos(2 * M_PI * (f0 + (fk - f0) * t / totalTime) * t + phi0);
        channel.add(sample);
    }
    
    channel_wrapper.setChannel(channel);
    addChannel(channel_wrapper);
}
} // namespace ctrl




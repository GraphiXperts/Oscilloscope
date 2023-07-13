#ifndef _CONTROLLERS_MODELING_HPP_
#define _CONTROLLERS_MODELING_HPP_
#include <memory>
#include <models/time.hpp>

namespace ctrl {

class Modeling {

public:
    // Добавляет новый канал в сигнал
    // start_time - время начала отчёта в UNIXTIME
    // n - задержка сигнала
    // N - количество семплов
    //freq - частота дискретизации
    // j = номер канала(конкретно этого типа)
    static void delayedSingleImpulse(mdl::time_t start_time, const uint64_t N,  const double freq, const uint64_t n, const uint64_t j);
    
    static void delayedSingleHop(mdl::time_t start_time, const uint64_t N,  const double freq, const uint64_t n, const uint64_t j);

    static void sampledDecreasingExponent(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const uint64_t j);

    static void sampledSineWave(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double circFreq, const double initPhase, const uint64_t j);

    static void meander(mdl::time_t start_time, const uint64_t N,  const double freq, const uint32_t L, const uint64_t j);

    static void saw(mdl::time_t start_time, const uint64_t N,  const double freq, const uint32_t L, const uint64_t j);

    // С непрерывным аргументом :

    static void exponentialEnvelope(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double tau, const double f, const double phi, const uint64_t j);

    static void balanceEnvelope(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double f0, const double fn, const double phi, const uint64_t j);

    static void tonalEnvelope(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double f0, const double fn, const double phi, const double m,  const uint64_t j);

    static void LFM(mdl::time_t start_time, const uint64_t N,  const double freq, const double a, const double f0, const double fk, const double phi0, const uint64_t j);   
};
} // namespace ctrl
#endif  // _CONTROLLERS_MODELING_HPP_
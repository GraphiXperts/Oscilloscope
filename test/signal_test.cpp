#include <assert.h>

#include <iostream>
#include <models/signal.hpp>

double drand() {
    return double(std::rand() * std::rand() * std::rand()) / 1e+3;
}

int main() {
    {
        std::cout << "Testing ChannelInfo..." << std::endl;

        mdl::Channel channel;

        int n = 100;

        mdl::ChannelInfo info = {L"", L"",       0,        INFINITY, -INFINITY,
                                 0,   -INFINITY, INFINITY, 0};

        for (int i = 0; i < n; i++) {
            mdl::Sample a = {drand(), i};
            channel.add(a);

            info.start_time    = std::min(info.start_time, a.time);
            info.finish_time   = std::max(info.finish_time, a.time);
            info.duration_time = info.finish_time - info.start_time;

            if (i != 0) {
                long double freq =
                    1.0 / (channel.at(i).time - channel.at(i - 1).time);

                info.max_frequency = std::max(info.max_frequency, freq);
                info.min_frequency = std::min(info.min_frequency, freq);
                info.avg_frequency =
                    (info.avg_frequency * (info.sample_count - 1) + freq) /
                    (info.sample_count);
            }
            info.sample_count++;

        }

        mdl::ChannelInfo result = getInfo(channel);

		assert(result.sample_count == info.sample_count);
		assert(result.start_time == info.start_time);
		assert(result.finish_time == info.finish_time);
		assert(result.duration_time == info.duration_time);
		assert(result.max_frequency == info.max_frequency);
		assert(result.min_frequency == info.min_frequency);
		assert(result.avg_frequency == info.avg_frequency);

        std::cout << "Test 1: Ok" << std::endl;
    }

	{

        mdl::Channel channel;

        int n = 100;

        mdl::ChannelInfo info = {L"", L"",       0,        INFINITY, -INFINITY,
                                 0,   -INFINITY, INFINITY, 0};

        for (int i = 0; i < n; i++) {
			mdl::Sample a;
			if (i == 0)
				a = {drand(), drand()};
			else
            	a = {drand(), channel.at(channel.size() - 1).time + drand() / 1e4};
            channel.add(a);

            info.start_time    = std::min(info.start_time, a.time);
            info.finish_time   = std::max(info.finish_time, a.time);
            info.duration_time = info.finish_time - info.start_time;

            if (i != 0) {
                long double freq =
                    1.0 / (channel.at(i).time - channel.at(i - 1).time);

                info.max_frequency = std::max(info.max_frequency, freq);
                info.min_frequency = std::min(info.min_frequency, freq);
                info.avg_frequency =
                    (info.avg_frequency * (info.sample_count - 1) + freq) /
                    (info.sample_count);
            }
            info.sample_count++;

        }

        mdl::ChannelInfo result = getInfo(channel);

		assert(result.sample_count == info.sample_count);
		assert(result.start_time == info.start_time);
		assert(result.finish_time == info.finish_time);
		assert(result.duration_time == info.duration_time);
		assert(result.max_frequency == info.max_frequency);
		assert(result.min_frequency == info.min_frequency);
		assert(result.avg_frequency == info.avg_frequency);

        std::cout << "Test 2: Ok" << std::endl;
    }
}
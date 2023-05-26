#include <models/channel.hpp>
#include <iostream>
#include <random>
#include <ctime>
#include <assert.h>

double drand() {
	return double(std::rand() * std::rand() * std::rand()) / 1e+3;
}

int main() {
	std::srand(std::time(NULL));

	{
		std::cout << "Testing channel..." << std::endl;

		mdl::Channel channel;

		int n = 100;
		std::vector<mdl::Sample> samples;

		for (int i = 0; i < n; i++) {
			mdl::Sample a = {drand(), drand()};
			samples.push_back(a);
			channel.add(a);
		}

		mdl::Range range = *channel.range(0, channel.size() - 1);
		
		auto s = samples.begin();
		for (auto& el : range) {
			assert(el.time == s->time);
			assert(el.value == s->value);
			++s;
		}

		std::cout << "Test 1: Ok" << std::endl;

	}

	{
		mdl::Channel channel;

		int n = 100;
		std::vector<mdl::Sample> samples;

		for (int i = 0; i < n; i++) {
			mdl::Sample a = {drand(), drand()};
			samples.push_back(a);
			channel.add(a);
		}

		mdl::Range range = *channel.range(20, channel.size() - 20);
		
		auto s = samples.begin() + 20;
		for (auto& el : range) {
			assert(el.time == s->time);
			assert(el.value == s->value);
			++s;
		}

		std::cout << "Test 2: Ok" << std::endl;

	}

	{
		mdl::Channel channel;

		int n = 100;
		std::vector<mdl::Sample> samples;

		for (int i = 0; i < n; i++) {
			mdl::Sample a = {drand(), drand()};
			samples.push_back(a);
			channel.add(a);
		}

		assert(!bool(channel.range(20, channel.size() + 1)));

		std::cout << "Test 3: Ok" << std::endl;

	}

	{
		mdl::Channel channel;

		int n = 100;
		std::vector<mdl::Sample> samples;

		for (int i = 0; i < n; i++) {
			mdl::Sample a = {drand(), drand()};
			samples.push_back(a);
			channel.add(a);
		}

		assert(!bool(channel.range(-1, channel.size() + 1)));

		std::cout << "Test 4: Ok" << std::endl;

	}

	{
		mdl::Channel channel;

		int n = 100;
		std::vector<mdl::Sample> samples;

		for (int i = 0; i < n; i++) {
			mdl::Sample a = {drand(), drand()};
			samples.push_back(a);
			channel.add(a);
		}

		assert(bool(channel.range(20, channel.size())));

		std::cout << "Test 5: Ok" << std::endl;

	}

	{
		mdl::Channel channel;

		int n = 100;
		std::vector<mdl::Sample> samples;

		for (int i = 0; i < n; i++) {
			mdl::Sample a = {drand(), drand()};
			samples.push_back(a);
			channel.add(a);
		}

		assert(!bool(channel.range(20, 10)));

		std::cout << "Test 6: Ok" << std::endl;

	}

}
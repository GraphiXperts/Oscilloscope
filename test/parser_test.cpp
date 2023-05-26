#include <models/parser.hpp>
#include <models/signal_parsers/txt_parser.hpp>
#include <iostream>
#include <assert.h>

int main() {

	mdl::FileParser parser;

	parser.addParser("txt", std::make_shared<mdl::TxtParser>());

	std::cout << "Parsers testing..." << std::endl;

	{
		auto result = parser.parse("inputs/earthquake.txt");

		assert(bool(result));

		std::cout << "Test 1: Ok" << std::endl;
		
	}

	std::cout << "Tests for parsers will be finished later..." << std::endl;
}
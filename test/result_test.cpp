#include <models/result.hpp>
#include <functional>
#include <iostream>
#include <assert.h>

int main() {
	{
		std::cout << "Testing result..." << std::endl;
		std::function<mdl::Result(bool)> f = [](bool a){
			if (a)
				return mdl::Ok();
			else
				return mdl::Err("It's bad...");
		};

		assert(bool(f(true)));
		assert(!bool(f(false)));
		assert(f(false).m() == "It's bad...");
		std::cout << "Good!" << std::endl;
	}

	{
		std::cout << "Testing vresult..." << std::endl;
		std::function<mdl::VResult<int>(int)> f = [](int a) -> mdl::VResult<int>{
			if (a == 0)
				return mdl::Err("Something wrong!");
			else
				return mdl::Ok(a);
		};

		assert(*f(1) == 1);
		assert(*f(2) == 2);
		assert(!bool(f(false)));
		assert(f(false).m() == "Something wrong!");
		std::cout << "Good!" << std::endl;
	}
}
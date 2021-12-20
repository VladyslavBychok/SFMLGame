#include "Program.h"

using namespace sf;



int main() {

	auto program = std::make_unique< Program >();

	try
	{
		program->launch();
	}
	catch (const std::runtime_error& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Undefind eror" << std::endl;
	}

	return 0;
}
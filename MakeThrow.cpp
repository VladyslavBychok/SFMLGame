#include "makeThrow.h"

#include <string>
#include <stdexcept>

void makeThrow(std::string_view message, std::string_view function, int line) {
	std::string erorMessage = message.data();
	erorMessage += "\n Has occured inside : ";
	erorMessage += function;
	erorMessage += "\n At line: ";
	erorMessage += std::to_string(line);

	throw std::runtime_error(erorMessage);
}
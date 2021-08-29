#pragma once
#include <string_view>

void makeThrow(std::string_view message, std::string_view function, int line);

#define MAKE_THROW(msg) makeThrow( msg, __FUNCTION__, __LINE__)
#include "Renderer.h"

#include <cassert>
#include <tuple>
#include <fstream>
#include <String>
#include <sstream>
#include <iostream>

namespace PerigordGL
{
	std::tuple<std::string, std::string> parseShader(const std::string filepath);
	uint32_t compileShader(uint32_t type, const std::string& source);
	uint32_t createShader(const std::string& vertexShader, const std::string& fragmentShader);
}
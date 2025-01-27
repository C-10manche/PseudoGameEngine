#pragma once

#include <unordered_map>
#include <string>
#include <array>

class Material
{
public:
	std::unordered_map<std::string, std::array<float, 3>> vec3_properties;
	std::string shader_name;

	Material(std::string shader_name);
};


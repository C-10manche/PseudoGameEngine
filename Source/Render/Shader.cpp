#include "Shader.h"	 
#include <string>	
#include <fstream> 
#include <glad/glad.h>
#include <iostream>
#include "../Utils/MyMath.h"

Shader::Shader() : id(0) { }

Shader::Shader(std::string file_path) : id(0) {
	std::ifstream shader_file;
	shader_file.open(file_path);


	if (shader_file.is_open()) {
		std::string current_line;
		std::string sources[2];
		int index = -1;
		while (std::getline(shader_file, current_line)) {
			if (current_line.find("#VERTEX SHADER") != std::string::npos)
			{
				index = 0;
			}
			else if (current_line.find("#FRAGMENT SHADER") != std::string::npos)
			{
				index = 1;
			}
			else if (index != -1)	
			{
				sources[index] += current_line + '\n';
			}
		}

		//vertex shader setup
		const char* vertex_source = sources[0].c_str();
		unsigned int vertex_shader_id = compile_shader(vertex_source, GL_VERTEX_SHADER);


		//fragment shader setup
		const char* fragment_source = sources[1].c_str();
		unsigned int fragment_shader_id = compile_shader(fragment_source, GL_FRAGMENT_SHADER);


		this->id = glCreateProgram();
		glAttachShader(this->id, vertex_shader_id);
		glAttachShader(this->id, fragment_shader_id);
		glLinkProgram(this->id);

		check_program_errors(this->id);

		glDeleteShader(vertex_shader_id);
		glDeleteShader(fragment_shader_id);
		shader_file.close();
	}
}

Shader::~Shader() {
	if(this->id != 0) 
		glDeleteProgram(this->id);
}

void Shader::check_shader_errors(unsigned int shader_id, int shader_type)
{
	int compiled;
	char info[512];
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compiled);

	if (compiled == false)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, info);
		const char* type;
		switch (shader_type) {
		case GL_VERTEX_SHADER:
			type = "VERTEX";
			break;
		case GL_FRAGMENT_SHADER:
			type = "FRAGMENT";
			break;
		default:
			type = "UNKNOWN";
			break;
		}
		std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << info << std::endl;
	}
}

void Shader::check_program_errors(unsigned int program_id)
{
	int linked;
	char info[512];
	glGetProgramiv(program_id, GL_LINK_STATUS, &linked);
	if (linked == false)
	{
		glGetProgramInfoLog(program_id, 512, NULL, info);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info << std::endl;
	}
}

unsigned int Shader::compile_shader(const char* source, int shader_type){
	unsigned int shader_id = glCreateShader(shader_type);
	glShaderSource(shader_id, 1, &source, NULL);
	glCompileShader(shader_id);

	check_shader_errors(shader_id, shader_type);

	return shader_id;
}

void Shader::use()
{
	glUseProgram(this->id);
}

void Shader::set_bool(const std::string& name, bool value) const {
	int uniform_location = glGetUniformLocation(this->id, name.c_str());
	glUniform1i(uniform_location, (int)value);
}

void Shader::set_int(const std::string& name, int value) const {
	int uniform_location = glGetUniformLocation(this->id, name.c_str());
	glUniform1i(uniform_location, value);
}

void Shader::set_float(const std::string& name, float value) const {
	int uniform_location = glGetUniformLocation(this->id, name.c_str());
	glUniform1f(uniform_location, value);
}

void Shader::set_vec3(const std::string& name, float* value) const {
	int uniform_location = glGetUniformLocation(this->id, name.c_str());
	glUniform3fv(uniform_location, 1, value);
}

void Shader::set_mat4(const std::string& name, float* value) const {
	int uniform_location = glGetUniformLocation(this->id, name.c_str());
	glUniformMatrix4fv(uniform_location, 1, GL_TRUE, value);
}

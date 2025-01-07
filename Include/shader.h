#pragma once 
#include <string>

class Shader
{
public :
	unsigned int id;
	
	Shader();
	Shader(std::string file_path);
	~Shader();
	void use();
			 
	void set_bool(const std::string& name, bool value) const;
	void set_int(const std::string& name, int value) const;
	void set_float(const std::string& name, float value) const;
	void set_mat4(const std::string& name, float* value) const;

private:

	void check_shader_errors(unsigned int _id, int shader_type);
	void check_program_errors(unsigned int _id);
	unsigned compile_shader(const char* source, int shader_type);

};

#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include "shader.hpp"
#include "shader_program.hpp"
#include <map>

class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	void loadProgram(std::string vert_shader_file, 
		GLuint vert_shader,
		std::string frag_shader_file,
		GLuint frag_shader);

	void loadProgram(std::string vert_shader_file,
		GLuint vert_shader,
		std::string frag_shader_file,
		GLuint frag_shader,
		std::string opt_shader_file,
		GLuint opt_shader, 
		eProgramMode mode);

	void loadProgram(std::string vert_shader_file,
		GLuint vert_shader,
		std::string frag_shader_file,
		GLuint frag_shader, 
		std::string tess_shader_file,
		GLuint tess_shader,
		std::string geom_shader_file,
		GLuint geom_shader);

private:
	std::map<GLuint, GLuint> shader_map_;
};

#endif

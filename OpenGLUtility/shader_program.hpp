#ifndef SHADER_PROGRAM_HPP
#define SHADER_PROGRAM_HPP

#include "gl_includes.hpp"
#include "shader.hpp"

class ShaderProgram
{
public:
	ShaderProgram(Shader* shaders, unsigned int mode);
private:
	const GLuint program_;
};

#endif
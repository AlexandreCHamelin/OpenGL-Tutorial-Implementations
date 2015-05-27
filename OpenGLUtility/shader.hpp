#ifndef SHADER_HPP
#define SHADER_HPP

#include "gl_includes.hpp"

class Shader
{
public:
	Shader(std::string shaderFile, GLenum shaderType);
	GLuint get_shader() const;
private:
	const std::string shaderFile_;
	const GLuint shader_;

	bool loadShaderFile() const;
	void logShaderCompilation() const;
};
#endif
